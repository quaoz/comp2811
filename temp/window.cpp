// COMP2811 Coursework 2 sample solution: main window

#include "window.hpp"

#include <QtWidgets>
#include <QtCharts/QChartView>
#include <QtCharts/QLineSeries>
#include <QtCharts/QChart>
//#include <QtCore/QDateTime>
#include <QtCore/QVector>
//#include <QtCharts/QDateTimeAxis>
#include <QDateTime>
#include <QString>

#include <iostream>
#include <stdexcept>
#include <utility>  // for std::pair
#include <vector>

//using namespace std;

static const int MIN_WIDTH = 620;

QuakeWindow::QuakeWindow() : QMainWindow() {
  //createMainWidget();
  createFileSelectors();
  createButtons();
  createToolBar();
  createStatusBar();
  addFileMenu();
  addHelpMenu();
  addSelectPollutantMenu();

  setMinimumWidth(MIN_WIDTH);
  setWindowTitle("Water Quality Tool");
}

// void QuakeWindow::createMainWidget() {
//   table = new QTableView();
//   table->setModel(&model);

//   QFont tableFont = QFontDatabase::systemFont(QFontDatabase::FixedFont);
//   table->setFont(tableFont);

//   QLineSeries *POLLUTANTSERIES = new QLineSeries();
//   std::vector<std::pair<std::string, double>> graphData = pollutantGraph.getData();

//   for (const auto& dataPair : graphData) {
//     //DateTime dateTime = QDateTime::fromString(QString::fromStdString(pair.first), "yyyy-MM-ddTHH:mm:ss");
//     //POLLUTANTSERIES->append(dateTime.toMSecsSinceEpoch(), dataPair.second);
//     QString dateTimeString = QString::fromStdString(dataPair.first);
//     QDateTime dateTime = QDateTime::fromString(dateTimeString, "yyyy-MM-ddTHH:mm:ss");
//     qreal xValue = dateTime.toMSecsSinceEpoch();
//     POLLUTANTSERIES->append(xValue, dataPair.second);

//     //POLLUTANTSERIES->append(dataPair.first, dataPair.second);
//   }

//   QChart *POLLUTANTCHART = new QChart();
//   POLLUTANTCHART->addSeries(POLLUTANTSERIES);
//   POLLUTANTCHART->createDefaultAxes();

//   QChartView *POLLUTANTCHARTVIEW = new QChartView(POLLUTANTCHART);
//   POLLUTANTCHARTVIEW->setRenderHint(QPainter::Antialiasing);

//   //setCentralWidget(POLLUTANTCHARTVIEW);


//   setCentralWidget(table);

// }
//void QuakeWindow::createGraph() {

  //cout << "Graph create";

  // QLineSeries *POLLUTANTSERIES = new QLineSeries();
  // std::vector<std::pair<std::string, double>> graphData = pollutantGraph.getData();

  // for (const auto& dataPair : graphData) {
  //   //DateTime dateTime = QDateTime::fromString(QString::fromStdString(pair.first), "yyyy-MM-ddTHH:mm:ss");
  //   //POLLUTANTSERIES->append(dateTime.toMSecsSinceEpoch(), dataPair.second);
  //   QString dateTimeString = QString::fromStdString(dataPair.first);
 //QLineSeries *POLLUTANTSERIES = new QLineSeries();
  // std::vector<std::pair<std::string, double>> graphData = pollutantGraph.getData();

  // for (const auto& dataPair : graphData) {
  //   //DateTime dateTime = QDateTime::fromString(QString::fromStdString(pair.first), "yyyy-MM-ddTHH:mm:ss");
  //   //POLLUTANTSERIES->append(dateTime.toMSecsSinceEpoch(), dataPair.second);
  //   QString dateTimeString = QString::fromStdString(dataPair.first);
  //   QDateTime dateTime = QDateTime::fromString(dateTimeString, "yyyy-MM-ddTHH:mm:ss");
  //   qreal xValue = dateTime.toMSecsSinceEpoch();
  //   POLLUTANTSERIES->append(xValue, dataPair.second);

  //   //POLLUTANTSERIES->append(dataPair.first, dataPair.second);
  // }

  // QChart *POLLUTANTCHART = new QChart();
  // POLLUTANTCHART->addSeries(POLLUTANTSERIES);
  // POLLUTANTCHART->createDefaultAxes();

  // QChartView *POLLUTANTCHARTVIEW = new QChartView(POLLUTANTCHART);
  // POLLUTANTCHARTVIEW->setRenderHint(QPainter::Antialiasing);

  // setCentralWidget(POLLUTANTCHARTVIEW);
  //   //POLLUTANTSERIES->append(dataPair.first, dataPair.second);
  // }

  // QChart *POLLUTANTCHART = new QChart();
  // POLLUTANTCHART->addSeries(POLLUTANTSERIES);
  // POLLUTANTCHART->createDefaultAxes();

  // QChartView *POLLUTANTCHARTVIEW = new QChartView(POLLUTANTCHART);
  // POLLUTANTCHARTVIEW->setRenderHint(QPainter::Antialiasing);

  // setCentralWidget(POLLUTANTCHARTVIEW);

  // if dataset.size() != 0 {
  //   Sample sample = 
  //   std::cout << 
  // }
  // //std::vector<std::pair<std::string, double>> QuakeDataset::getSpecificPollutantData(std::string pollutantName){
  // //std::vector<std::pair<std::string, double>> pollutantData;
  // std::vector<QuakeDataset> specificPollutantData(const )
  // for (const auto& point : pollutantData) {
  //   if (point.getDeterminand().getLabel() == pollutantName) {

  //     //pollutantData.push_back(std::make_pair(point.getSampleDateTime(), point.getResult()));
  //   };
  // }

  // //LAST CODING HERE

  // std::vector<std::pair<std::string, double>> pollutantData = QuakeDataset.getSpecificPollutantData("Endrin");
  
  // QLineSeries *series = new QLineSeries();
  // for (const auto )


  // pollutantGraph = new QGraph();
  // pollutant/* void QuakeWindow::createMainWidget() {
//   table = new QTableView();
//   table->setModel(&model);

//   QFont tableFont = QFontDatabase::systemFont(QFontDatabase::FixedFont);
//   table->setFont(tableFont);


//   setCentralWidget(table);
// }


void QuakeWindow::createMainWidget() {

  pollutantSeries = new QLineSeries();

  //pollutantSeries->append(10,15);
  //pollutantSeries->append(12,10);

  double counter = 0;
  
  for(int i = 0; i<(model.rowCount(QModelIndex())); i++) {
    Sample SampleData = model.getSample(i);
    //Determinand determinandData = model.getSample(i);
    
    
    if (SampleData.getDeterminand().getLabel() == "Endrin"){

      //pollutantSeries->append(10,15);
      //pollutantSeries->append(12,10);
      pollutantSeries->append(counter, SampleData.getResult());

      // pollutantSeries->append(counter, SampleData.getResult());
      counter = counter + 1.0;
    }
  }

  QChart *pollutantChart = new QChart();
  pollutantChart->addSeries(pollutantSeries);
  pollutantChart->setTitle("Endrin");

  QValueAxis *axisX = new QValueAxis();
  // axisX->setRange(0, 0.01);
  // pollutantChart->addAxis(axisX, Qt::AlignBottom);

  // pollutantSeries->attachAxis(axisX);

  QValueAxis *axisY = new QValueAxis();
  // axisY->setRange(0, 100);
  // pollutantChart->addAxis(axisY, Qt::AlignLeft);
  // pollutantSeries->attachAxis(axisY);

  pollutantChart->createDefaultAxes();

  QChartView *pollutantView = new QChartView(pollutantChart);
  pollutantView->setRenderHint(QPainter::Antialiasing);

  setCentralWidget(pollutantView);


  // table = new QTableView();
  // table->setModel(&model);

  // QFont tableFont = QFontDatabase::systemFont(QFontDatabase::FixedFont);
  // table->setFont(tableFont);


  // setCentralWidget(table);
}

void QuakeWindow::createFileSelectors() {
  QStringList periodOptions;
  periodOptions << "2024"
                << "2023"
                << "2023"
                << "2022"
                << "2021"
                << "2020"
                << "2019"
                << "2018"
                << "2017"
                << "2016"
                << "2015"
                << "2014"
                << "2013"
                << "2012"
                << "2011"
                << "2010"
                << "2009"
                << "2008"
                << "2007"
                << "2006"
                << "2005"
                << "2004"
                << "2003"
                << "2002"
                << "2001"
                << "2000";
  period = new QComboBox();
  period->addItems(periodOptions);
}

void QuakeWindow::createButtons() {
  loadButton = new QPushButton("Load");
  connect(loadButton, SIGNAL(clicked()), this, SLOT(openCSV()));
}

void QuakeWindow::createToolBar() {
  QToolBar* toolBar = new QToolBar();
  QLabel* periodLabel = new QLabel("Period");
  periodLabel->setAlignment(Qt::AlignVCenter);
  toolBar->addWidget(periodLabel);
  toolBar->addWidget(period);

  toolBar->addSeparator();

  toolBar->addWidget(loadButton);

  addToolBar(Qt::LeftToolBarArea, toolBar);
}

void QuakeWindow::createStatusBar() {
  fileInfo = new QLabel("Current file: <none>");
  QStatusBar* status = statusBar();
  status->addWidget(fileInfo);
}

void QuakeWindow::addFileMenu() {
  QAction* locAction = new QAction("Set Data &Location", this);
  locAction->setShortcut(QKeySequence(Qt::CTRL | Qt::Key_L));
  connect(locAction, SIGNAL(triggered()), this, SLOT(setDataLocation()));

  QAction* closeAction = new QAction("Quit", this);
  closeAction->setShortcut(QKeySequence::Close);
  connect(closeAction, SIGNAL(triggered()), this, SLOT(close()));

  QMenu* fileMenu = menuBar()->addMenu("&File");
  fileMenu->addAction(locAction);
  fileMenu->addAction(closeAction);
}

void QuakeWindow::addHelpMenu() {
  QAction* aboutAction = new QAction("&About", this);
  connect(aboutAction, SIGNAL(triggered()), this, SLOT(about()));

  QAction* aboutQtAction = new QAction("About &Qt", this);
  connect(aboutQtAction, SIGNAL(triggered()), qApp, SLOT(aboutQt()));

  QMenu* helpMenu = menuBar()->addMenu("&Help");
  helpMenu->addAction(aboutAction);
  helpMenu->addAction(aboutQtAction);
}

void QuakeWindow::addSelectPollutantMenu() {

  QMenu *selectMenu = menuBar()->addMenu("SelectPollutant");

  QComboBox *selectPollutant = new QComboBox(this);
  selectPollutant->addItem("option 1");

  QWidgetAction *comboAction = new QWidgetAction(this);
  comboAction->setDefaultWidget(selectPollutant);

  selectMenu->addAction(comboAction);
}



void QuakeWindow::setDataLocation() {
  QString directory = QFileDialog::getExistingDirectory(
    this, "Data Location", ".",
    QFileDialog::ShowDirsOnly | QFileDialog::DontResolveSymlinks);

  if (directory.length() > 0) { dataLocation = directory; }
}

void QuakeWindow::openCSV() {
  if (dataLocation == "") {
    QMessageBox::critical(this, "Data Location Error",
                          "Data location has not been set!\n\n"
                          "You can specify this via the File menu.");
    return;
  }

  auto filename = QString("Y-%1.csv").arg(period->currentText());

  auto path = dataLocation + "/" + filename;

  try {
    model.updateFromFile(path);
  } catch (const std::exception& error) {
    QMessageBox::critical(this, "CSV File Error", error.what());
    return;
  }

  fileInfo->setText(QString("Current file: <kbd>%1</kbd>").arg(filename));
  //table->resizeColumnsToContents();

  createMainWidget();
}

void QuakeWindow::about() {
  QMessageBox::about(
    this, "About Water Quality Tool",
    "Quake Tool displays and analyzes water quality data loaded from"
    "a CSV file produced by the Environment Agency Water Quality "
    "Archive.\n\n");
}

// void QuakeWindow::getPollutantData() {
//   int datasetSize = dataset.size();

//   for(int i = 0; i<datasetSize; i++) {
//     Sample q = dataset[i.row()];
//     if (q.getDeterminand().getLabel() == "Endrin"){
//       pollutantData.append(QPointF(counter, q.getResult()));
//       counter = counter + 1.0;
//     }
//   }
// }