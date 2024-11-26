// #include <QApplication>
// #include "pollutantoverview.hpp"

// int main(int argc, char* argv[])
// {
//   QApplication app(argc, argv);

//   MyWindow pollutantoverview;
//   pollutantoverview.show();

//   return app.exec();
// }

#include <QApplication>
#include <QMainWindow>
#include <QMenuBar>
#include <QMenu>
#include <QAction>
#include <QLineEdit>
#include <QToolBar>
#include <QVBoxLayout>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    QMainWindow mainWindow;

    // Create a menu bar
    QMenuBar *menuBar = mainWindow.menuBar();

    // Create a file menu
    QMenu *fileMenu = menuBar->addMenu("File");

    // Create actions for the file menu
    QAction *newAction = new QAction("New", &mainWindow);
    QAction *openAction = new QAction("Open", &mainWindow);
    QAction *exitAction = new QAction("Exit", &mainWindow);

    // Add actions to the file menu
    fileMenu->addAction(newAction);
    fileMenu->addAction(openAction);
    fileMenu->addSeparator();
    fileMenu->addAction(exitAction);

    // Connect the exit action to close the application
    QObject::connect(exitAction, &QAction::triggered, &app, &QApplication::quit);

    QWidget *centralWidget = new QWidget(&mainWindow);
    QVBoxLayout *layout = new QVBoxLayout(centralWidget);

    // Create a toolbar for the search bar
    QToolBar *searchToolBar = new QToolBar("Search");
    QLineEdit *searchLineEdit = new QLineEdit();
    searchLineEdit->setPlaceholderText("Search...");
    searchToolBar->addWidget(searchLineEdit);

    // Add the search toolbar to the main window
    //mainWindow.addToolBar(searchToolBar);
    layout->addWidget(searchToolBar);

    

    QWidget *spaceForGraph = new QWidget();
    spaceForGraph->setStyleSheet("background-color: lightgray; border: 1px solid black;");
    spaceForGraph->setFixedSize(200,200);

    layout->addWidget(spaceForGraph);
    layout->addStretch();

    mainWindow.setCentralWidget(centralWidget);

    mainWindow.setWindowTitle("Pollutant overview");
    mainWindow.resize(800, 600);
    mainWindow.show();

    return app.exec();
}

// #include <QApplication>
// #include <QMainWindow>
// #include <QMenuBar>
// #include <QMenu>
// #include <QAction>

// int main(int argc, char *argv[])
// {
//     QApplication app(argc, argv);

//     QMainWindow mainWindow;

//     // Create a menu bar
//     QMenuBar *menuBar = mainWindow.menuBar();

//     // Create a file menu
//     QMenu *fileMenu = menuBar->addMenu("File");

//     // Create actions for the file menu
//     QAction *newAction = new QAction("New", &mainWindow);
//     QAction *openAction = new QAction("Open", &mainWindow);
//     QAction *exitAction = new QAction("Exit", &mainWindow);

//     // Add actions to the file menu
//     fileMenu->addAction(newAction);
//     fileMenu->addAction(openAction);
//     fileMenu->addSeparator(); // Add a separator line
//     fileMenu->addAction(exitAction);

//     // Connect the exit action to close the application
//     QObject::connect(exitAction, &QAction::triggered, &app, &QApplication::quit);

//     mainWindow.setWindowTitle("Qt Menu Bar Example");
//     mainWindow.resize(400, 300);
//     mainWindow.show();

//     return app.exec();
// }


// #include <QtWidgets>

// int main(int argc, char* argv[])
// {
//   QApplication app(argc, argv);

//   QLabel* widget = new QLabel("<h1>Hello World!</h1>");
//   widget->show();

//   return app.exec();
// }



// #include <QApplication>
// #include "mainwindow.h"

// int main(int argc, char* argv[]) {
//     QApplication app(argc, argv);

//     MainWindow mainWindow;
//     mainWindow.resize(600, 400);
//     mainWindow.show();

//     return app.exec();
// }