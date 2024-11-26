#include "mainwindow.h"

MainWindow::MainWindow(QWidget* parent) : QMainWindow(parent) {
    setWindowTitle("Navigation Example");

    // Create menu bar
    QMenuBar* menuBar = new QMenuBar(this);
    setMenuBar(menuBar);

    // Add menus
    QMenu* navigationMenu = menuBar->addMenu("Navigate");

    // Add actions to the menu
    QAction* goToWindow1 = new QAction("Go to Window 1", this);
    QAction* goToWindow2 = new QAction("Go to Window 2", this);

    navigationMenu->addAction(goToWindow1);
    navigationMenu->addAction(goToWindow2);

    // Create windows
    window1 = new Window1();
    window2 = new Window2();

    // Set default central widget
    setCentralWidget(window1);

    // Connect actions to switching logic
    connect(goToWindow1, &QAction::triggered, this, &MainWindow::showWindow1);
    connect(goToWindow2, &QAction::triggered, this, &MainWindow::showWindow2);
}

void MainWindow::showWindow1() {
    setCentralWidget(window1);
}

void MainWindow::showWindow2() {
    setCentralWidget(window2);
}