#pragma once

#include <QMainWindow>
#include <QTabWidget>

#include "data/dataset.hpp"
#include "pages/card.hpp"
#include "pages/compliance.hpp"
#include "pages/dashboard.hpp"
#include "pages/fluorinated.hpp"
#include "pages/litter.hpp"
#include "pages/pollutants.hpp"
#include "pages/pops.hpp"

class QString;
class QComboBox;
class QLabel;
class QPushButton;

class PollutantPage;
class POPsPage;
class LitterPage;
class FluorinatedPage;

class QuakeWindow : public QMainWindow {
  Q_OBJECT

 public:
  QuakeWindow();
  void switchTab(int index) const { tabWidget->setCurrentIndex(index); }

 private:
  void createFileSelectors();
  void createButtons();
  void createToolBar();
  void createStatusBar();
  void addFileMenu();
  void addHelpMenu();
  void createTabBar();
  void update();

  QuakeDataset model;         // data model used by table
  QString dataLocation;     // location of CSV data files
  QComboBox* period;        // selector for quake feed time period
  QPushButton* loadButton;  // button to load a new CSV file
  QLabel* fileInfo;         // status bar info on current file
  QTabWidget* tabWidget;
  // WaterTable* table;
  LitterPage* litterPage;
  PollutantPage* pollutantPage;
  ComplianceDashboard* compliancePage;
  POPsPage* popsPage;
  FluorinatedPage* fluorinatedPage;
  MainDashboardPage* mainDashboardPage;

 private slots:
  void setDataLocation();
  void openCSV();
  void about();
};
