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

class WaterQalWindow : public QMainWindow {
  Q_OBJECT

 public:
  WaterQalWindow();
  void switchTab(int index) const { tabWidget->setCurrentIndex(index); }

 private:
  void createFileSelectors();
  void createButtons();
  void createToolBar();
  void createStatusBar();
  void addFileMenu();
  void addHelpMenu();
  void createTabBar();
  void pageUpdate();
  void update();

  WaterQalDataset model;

  QString dataLocation;
  QComboBox* period;
  QPushButton* loadButton;
  QLabel* fileInfo;
  QTabWidget* tabWidget;

  LitterPage* litterPage;
  PollutantPage* pollutantPage;
  ComplianceDashboard* compliancePage;
  POPsPage* popsPage;
  FluorinatedPage* fluorinatedPage;
  MainDashboardPage* mainDashboardPage;

  QDateTimeEdit* startTime;
  QDateTimeEdit* endTime;

 private slots:
  void onStartDateChanged(const QDateTime& dateTime);
  void onEndDateChanged(const QDateTime& dateTime);

  void setDataLocation();
  void openCSV();
  void about();
};
