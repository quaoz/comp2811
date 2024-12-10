#pragma once

#include <QMainWindow>
#include <QTabWidget>

#include "data/model.hpp"
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

class QuakeWindow : public QMainWindow {
  Q_OBJECT

 public:
  QuakeWindow();

 private:
  void createFileSelectors();
  void createButtons();
  void createToolBar();
  void createStatusBar();
  void addFileMenu();
  void addHelpMenu();
  void createTabBar();
  void update();

  QuakeModel model;         // data model used by table
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

  overviewCard* PCBCard;
  overviewCard* litterCard;
  overviewCard* fluoroCard;

 private slots:
  void setDataLocation();
  void openCSV();
  void about();
};
