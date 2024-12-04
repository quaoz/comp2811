// COMP2811 Coursework 2 sample solution: main window

#pragma once

#include <QMainWindow>

#include "model.hpp"

class QString;
class QComboBox;
class QLabel;
class QPushButton;
class QTableView;
class StatsDialog;
class QGraph;
class QLineSeries;

class QuakeWindow : public QMainWindow {
  Q_OBJECT

 public:
  QuakeWindow();

 private:
  void createMainWidget();
  void createFileSelectors();
  void createButtons();
  void createToolBar();
  void createStatusBar();
  void addFileMenu();
  void addHelpMenu();
  void addSelectPollutantMenu();
  void updatePollutantGraph();
  
  //void createGraph();

  QuakeModel model;         // data model used by table
  //PollutantGraph pollutantGraph;
  QString dataLocation;     // location of CSV data files
  QComboBox* period;        // selector for quake feed time period
  QPushButton* loadButton;  // button to load a new CSV file
  QTableView* table;        // table of quake data
  QLabel* fileInfo;         // status bar info on current file
  QGraph* pollutantGraph;
  QLineSeries *pollutantSeries;

 private slots:
  void setDataLocation();
  void openCSV();
  void about();
};