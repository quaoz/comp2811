#include <QtWidgets>
#include "window.hpp"
// #include <QMenuBar>
// #include <QMenu>
// #include <QAction>
// #include <QMessageBox>
// #include <QtCharts/QChartView>
// #include <QtCharts/QLineSeries>
// #include <QtCharts/QChart>


MyWindow::MyWindow()
{
  createWidgets();
  arrangeWidgets();

  // // Create the menu bar
  // QMenuBar *menuBar = new QMenuBar(this);

  // // Create the File menu
  // QMenu *fileMenu = menuBar->addMenu("File");

  // // Add actions to the File menu
  // QAction *newAction = new QAction("New", this);
  // QAction *openAction = new QAction("Open", this);
  // QAction *exitAction = new QAction("Exit", this);

  // // Add actions to the File menu
  // fileMenu->addAction(newAction);
  // fileMenu->addAction(openAction);
  // fileMenu->addSeparator(); // Add a separator
  // fileMenu->addAction(exitAction);

  // // Create the Help menu
  // QMenu *helpMenu = menuBar->addMenu("Help");

  // // Add actions to the Help menu
  // QAction *aboutAction = new QAction("About", this);
  // helpMenu->addAction(aboutAction);

  // // Set the menu bar
  // setMenuBar(menuBar);

  // // Connect actions to their slots
  // connect(newAction, &QAction::triggered, this, &MyWindow::onNew);
  // connect(openAction, &QAction::triggered, this, &MyWindow::onOpen);
  // connect(exitAction, &QAction::triggered, this, &MyWindow::close);
  // connect(aboutAction, &QAction::triggered, this, &MyWindow::onAbout);

  setWindowTitle("Pollutant Overview");
  setMinimumSize(320, 200);
}

// void MyWindow::onNew() {
//     QMessageBox::information(this, "New", "New file action triggered");
// }

// void MyWindow::onOpen() {
//     QMessageBox::information(this, "Open", "Open file action triggered");
// }

// void MyWindow::onAbout() {
//     QMessageBox::information(this, "About", "This is an example Qt application.");
// }

void MyWindow::createWidgets()
{
  // QWidget *widget = new QWidget;
  // setCenteralWidget(widget);

  // Create widgets on the heap using new

  // QChart *chart = new QChart();
  // QLineSeries *series = new QLineSeries();
  // series->append(0,0);
  // series->append(1,1);
  // chart->addSeries(series);
  // chart->createDefaultAxes();

  // QtCharts::QChartView *chartView = new QtCharts::QChartView(chart, this);
  // chartView->setRenderHint(QPainter::Antialiasing);

  // this->layout()->addWidget(chartView)

  // QWidget *parentWidget = new QWidget();
  // ChartWidget *chartWidget = new ChartWidget(parentWidget);

  // QVBoxLayout *parentLayout = new QVBoxLayout(parentWidget);
  // parentLayout->addWidget(chartWidget);

  // parentWidget->resize(800,600);
  // parentWidget->show();

}

void MyWindow::arrangeWidgets()
{
  // Create layout for widgets here
  // Remember to call setLayout!
}