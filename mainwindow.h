#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMenuBar>
#include <QWidget>
#include "window1.h"
#include "window2.h"

class MainWindow : public QMainWindow {
    Q_OBJECT
public:
    explicit MainWindow(QWidget* parent = nullptr);

private slots:
    void showWindow1();
    void showWindow2();

private:
    Window1* window1;
    Window2* window2;
};

#endif // MAINWINDOW_H