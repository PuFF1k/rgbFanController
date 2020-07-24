#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    //QGraphicsView view;
    //view.setFrameStyle(QFrame::NoFrame);

    handle =0;

    int res;
    unsigned char sendBuf[64];
    unsigned char responseBuf[64];
    wchar_t wstr[MAX_STR];
    //hid_device *handle;
    //int i;

    memset(&sendBuf, 0, 64);
    memset(&responseBuf, 0, 64);

    // Initialize the hidapi library
    res = hid_init();

    // Open the device using the VID, PID,
    // and optionally the Serial number.
    handle = hid_open(0x0483, 0x5750, NULL);

    if (handle != 0)
    {
        // Read the Manufacturer String
        res = hid_get_manufacturer_string(handle, wstr, MAX_STR);
        wprintf(L"Manufacturer String: %s\n", wstr);

        // Read the Product String
        res = hid_get_product_string(handle, wstr, MAX_STR);
        wprintf(L"Product String: %s\n", wstr);

        // Read the Serial Number String
        res = hid_get_serial_number_string(handle, wstr, MAX_STR);
        wprintf(L"Serial Number String: (%d) %s\n", wstr[0], wstr);

        // Read Indexed String 1
        res = hid_get_indexed_string(handle, 1, wstr, MAX_STR);
        wprintf(L"Indexed String 1: %s\n", wstr);

        uint32_t PWMSpeed = 55;

        sendBuf[0] = 0x0;
        memcpy(&sendBuf[1], &PWMSpeed, 4);

        res = hid_write(handle, sendBuf, 64);

        // Request state (cmd 0x81). The first byte is the report number (0x0).
        //buf[0] = 0x0;
        //buf[1] = 0x81;
        //res = hid_write(handle, buf, 65);

        // Read requested state
        res = hid_read(handle, responseBuf, 64);
    }

    res = hid_exit();


}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_dial_valueChanged(int value)
{
    if (handle != 0)
    {
        int32_t val = value;
        unsigned char sendBuf[64];
        unsigned char responseBuf[64];
        memset(&sendBuf, 0, 64);
        sendBuf[0] = 0x0;
        memcpy(&sendBuf[1], &val, 4);
        int res = hid_write(handle, sendBuf, 64);
        res = hid_read(handle, responseBuf, 64);

        uint32_t valueForPWMFromPC;

        memcpy(&valueForPWMFromPC, responseBuf, 4);

        memset( responseBuf, 0 ,0x40);
    }
}
