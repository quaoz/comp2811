// COMP2811 Coursework 2 sample solution: main window

#include "window.hpp"

#include <QtWidgets>
#include <iostream>
#include <stdexcept>

#include "sample.hpp"

static const int MIN_WIDTH = 620;

QuakeWindow::QuakeWindow() : QMainWindow() {
  createMainWidget();
  createFileSelectors();
  createButtons();
  createToolBar();
  createStatusBar();
  addFileMenu();
  addHelpMenu();
  createTabBar();

  setMinimumWidth(MIN_WIDTH);
  setWindowTitle("Water Quality Tool");
}

void QuakeWindow::createMainWidget() {
  // tabWidget = new QTabWidget();

  // table = new QTableView();
  // table->setModel(&model);

  // QFont tableFont = QFontDatabase::systemFont(QFontDatabase::FixedFont);
  // table->setFont(tableFont);

  // tabWidget->addTab(table, "Table");

  // setCentralWidget(tabWidget);
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

void QuakeWindow::createTabBar() {
  tabWidget = new QTabWidget();

  table1 = new QTableView();
  table1->setModel(&model);
  QFont tableFont = QFontDatabase::systemFont(QFontDatabase::FixedFont);
  table1->setFont(tableFont);

  tabWidget->addTab(table1, "Tab 1");

  createPieChart();

  setCentralWidget(tabWidget);
}

void QuakeWindow::createPieChart() {
  series = new QPieSeries();

  QChart* chart = new QChart();
  chart->addSeries(series);
  chart->setTitle("Litter Samples per Location");
  chart->legend()->setAlignment(Qt::AlignLeft);

  chartView = new QChartView(chart);
  chartView->setRenderHint(QPainter::Antialiasing);

  tabWidget->addTab(chartView, "Pie Chart");
}

void QuakeWindow::updatePieChart() {
  series->clear();

  // Count the number of litter samples per location
  std::map<std::string, int> litterCount;
  for (int i = 0; i < model.rowCount(QModelIndex()); ++i) {
    Sample sample = model.getSample(i);
    if (sample.getDeterminand().getLabel() == "BWP - O.L.") {
      litterCount[sample.getSamplingPoint().getLabel()]++;
    }
  }

  // Add data to the pie series
  for (const auto& entry : litterCount) {
    series->append(entry.first.c_str(), entry.second);
  }
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
  table1->resizeColumnsToContents();

  updatePieChart();
}

void QuakeWindow::about() {
  QMessageBox::about(
    this, "About Water Quality Tool",
    "Quake Tool displays and analyzes water quality data loaded from"
    "a CSV file produced by the Environment Agency Water Quality "
    "Archive.\n\n");
}
