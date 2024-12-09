#include "window.hpp"

#include <QtWidgets>

static const int MIN_WIDTH = 620;

QuakeWindow::QuakeWindow() : QMainWindow() {
  //reateFileSelectors();
  createButtons();
  createToolBar();
  createStatusBar();
  addFileMenu();
  addHelpMenu();
  createTabBar();

  setMinimumWidth(MIN_WIDTH);
  setWindowTitle("WaterQal Tool");
}

void QuakeWindow::update() {
  pollutantPage->update(&model);
  litterPage->update(&model);

  PCBCard->updateCard(&model, "PCB");
  litterCard->updateCard(&model, "BWP - O.L.");
  fluoroCard->updateCard(&model, "Fluoro");
  mainDashboardPage->update(&model, PCBCard, litterCard, fluoroCard);
}

void QuakeWindow::createTabBar() {
  tabWidget = new QTabWidget();

  PCBCard = new overviewCard("PCBs compounds overview", *tabWidget, this);
  litterCard =
    new overviewCard("Environmental litter overview", *tabWidget, this);
  fluoroCard =
    new overviewCard("Fluorinated compounds overview", *tabWidget, this);

  mainDashboardPage = new MainDashboardPage(this);
  tabWidget->addTab(mainDashboardPage, "Dashboard");

  pollutantPage = new PollutantPage(this);
  tabWidget->addTab(pollutantPage, "Polutant Overview");


  litterPage = new LitterPage(this);
  tabWidget->addTab(litterPage, "Environmental Litter Indicators");


  update();
  setCentralWidget(tabWidget);
}

void QuakeWindow::createButtons() {
  loadButton = new QPushButton("Load");
  connect(loadButton, SIGNAL(clicked()), this, SLOT(openCSV()));
}

void QuakeWindow::createToolBar() {
  QToolBar* toolBar = new QToolBar();

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

  auto filename = QString("Y-2024.csv");

  auto path = dataLocation + "/" + filename;

  try {
    model.updateFromFile(path);
  } catch (const std::exception& error) {
    QMessageBox::critical(this, "CSV File Error", error.what());
    return;
  }

  fileInfo->setText(QString("Current file: <kbd>%1</kbd>").arg(filename));
  update();
}

void QuakeWindow::about() {
  QMessageBox::about(
    this, "About Water Quality Tool",
    "Quake Tool displays and analyzes water quality data loaded from"
    "a CSV file produced by the Environment Agency Water Quality "
    "Archive.\n\n");
}
