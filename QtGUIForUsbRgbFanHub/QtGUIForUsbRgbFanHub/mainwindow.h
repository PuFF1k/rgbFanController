#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QLibrary>
#ifdef WIN32
#include <windows.h>
#endif
#include <QGraphicsView>
#include "hidapi.h"

#ifdef WIN32
typedef __int32 int32_t;
typedef unsigned __int32 uint32_t;
#endif

#define MAX_STR 255

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_dial_valueChanged(int value);


private:
    Ui::MainWindow *ui;
    hid_device *handle;
};

#endif // MAINWINDOW_H
