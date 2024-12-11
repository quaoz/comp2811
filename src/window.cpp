#include "window.hpp"

#include <QtWidgets>
#include <iostream>

#include "pages/card.hpp"
#include "pages/compliance.hpp"
#include "pages/dashboard.hpp"
#include "pages/fluorinated.hpp"
#include "pages/litter.hpp"
#include "pages/pollutants.hpp"
#include "pages/pops.hpp"

static const int MIN_WIDTH = 620;

QuakeWindow::QuakeWindow() : QMainWindow() {
  createFileSelectors();
  createButtons();
  createToolBar();
  createStatusBar();
  addFileMenu();
  addHelpMenu();
  createTabBar();

  setMinimumWidth(MIN_WIDTH);
  setWindowTitle(tr("WaterQal Tool"));  // TODO change no more quake tool
}

void QuakeWindow::update() {
  using std::chrono::duration;
  using std::chrono::duration_cast;
  using std::chrono::high_resolution_clock;
  using std::chrono::milliseconds;
  auto t1 = high_resolution_clock::now();

  pollutantPage->update(&model);
  popsPage->update(&model);
  litterPage->update(&model);
  fluorinatedPage->update(&model);
  compliancePage->update(&model);

  auto t2 = high_resolution_clock::now();
  duration<double, std::milli> ms_double = t2 - t1;
  std::cout << "updates: " << ms_double.count() << "ms\n";
}

void QuakeWindow::createTabBar() {
  tabWidget = new QTabWidget();

  pollutantPage = new PollutantPage(this);
  popsPage = new POPsPage(this);
  litterPage = new LitterPage(this);
  fluorinatedPage = new FluorinatedPage(this);
  compliancePage = new ComplianceDashboard(this);
  mainDashboardPage = new MainDashboardPage(
    pollutantPage->getCard(), popsPage->getCard(), litterPage->getCard(),
    fluorinatedPage->getCard(), this);

  tabWidget->addTab(mainDashboardPage, tr("Dashboard"));
  tabWidget->addTab(pollutantPage, tr("Polutant Overview"));
  tabWidget->addTab(popsPage, tr("Persistent Organic Pollutants"));
  tabWidget->addTab(litterPage, tr("Environmental Litter Indicators"));
  tabWidget->addTab(fluorinatedPage, tr("Fluorinated Compounds"));
  tabWidget->addTab(compliancePage, tr("Compliance Dashboard"));


  update();
  setCentralWidget(tabWidget);
}

// TODO: remove file period selector
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
  loadButton = new QPushButton(tr("Load"));
  connect(loadButton, SIGNAL(clicked()), this, SLOT(openCSV()));
}

void QuakeWindow::createToolBar() {
  QToolBar* toolBar = new QToolBar();
  QLabel* periodLabel = new QLabel(tr("Period"));
  periodLabel->setAlignment(Qt::AlignVCenter);
  toolBar->addWidget(periodLabel);
  toolBar->addWidget(period);

  toolBar->addSeparator();
  toolBar->addWidget(loadButton);

  addToolBar(Qt::LeftToolBarArea, toolBar);
}

void QuakeWindow::createStatusBar() {
  fileInfo = new QLabel(tr("Current file: <none>"));
  QStatusBar* status = statusBar();
  status->addWidget(fileInfo);
}

void QuakeWindow::addFileMenu() {
  QAction* locAction = new QAction(tr("Set Data &Location"), this);
  locAction->setShortcut(QKeySequence(Qt::CTRL | Qt::Key_L));
  connect(locAction, SIGNAL(triggered()), this, SLOT(setDataLocation()));

  QAction* closeAction = new QAction(tr("Quit"), this);
  closeAction->setShortcut(QKeySequence::Close);
  connect(closeAction, SIGNAL(triggered()), this, SLOT(close()));

  QMenu* fileMenu = menuBar()->addMenu(tr("&File"));
  fileMenu->addAction(locAction);
  fileMenu->addAction(closeAction);
}

void QuakeWindow::addHelpMenu() {
  QAction* aboutAction = new QAction(tr("&About"), this);
  connect(aboutAction, SIGNAL(triggered()), this, SLOT(about()));

  QAction* aboutQtAction = new QAction(tr("About &Qt"), this);
  connect(aboutQtAction, SIGNAL(triggered()), qApp, SLOT(aboutQt()));

  QMenu* helpMenu = menuBar()->addMenu(tr("&Help"));
  helpMenu->addAction(aboutAction);
  helpMenu->addAction(aboutQtAction);
}

void QuakeWindow::setDataLocation() {
  QString directory = QFileDialog::getExistingDirectory(
    this, "Data Location", ".",
    QFileDialog::ShowDirsOnly | QFileDialog::DontResolveSymlinks);

  if (directory.length() > 0) { dataLocation = directory; }
}

void QuakeWindow::openCSV() {
  if (dataLocation == "") {
    QMessageBox::critical(this, tr("Data Location Error"),
                          tr("Data location has not been set!\n\n"
                          "You can specify this via the File menu."));
    return;
  }

  auto filename = QString("Y-2024.csv");

  auto path = dataLocation + "/" + filename;

  try {
    model.updateFromFile(path);
  } catch (const std::exception& error) {
    QMessageBox::critical(this, tr("CSV File Error"), error.what());
    return;
  }

  fileInfo->setText(QString(tr("Current file: <kbd>%1</kbd>")).arg(filename));
  update();
}

void QuakeWindow::about() {
  QMessageBox::about(
    this, tr("About Water Quality Tool"),
    tr("Quake Tool displays and analyzes water quality data loaded from"
    "a CSV file produced by the Environment Agency Water Quality "
    "Archive.\n\n"));
}
