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
<<<<<<< HEAD
=======
class QGraph;
class QLineSeries;
>>>>>>> bd0649b (init)

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
<<<<<<< HEAD

  QuakeModel model;         // data model used by table
=======
  void addSelectPollutantMenu();
  void updatePollutantGraph();
  
  //void createGraph();

  QuakeModel model;         // data model used by table
  //PollutantGraph pollutantGraph;
>>>>>>> bd0649b (init)
  QString dataLocation;     // location of CSV data files
  QComboBox* period;        // selector for quake feed time period
  QPushButton* loadButton;  // button to load a new CSV file
  QTableView* table;        // table of quake data
  QLabel* fileInfo;         // status bar info on current file
<<<<<<< HEAD
=======
  QGraph* pollutantGraph;
  QLineSeries *pollutantSeries;
>>>>>>> bd0649b (init)

 private slots:
  void setDataLocation();
  void openCSV();
  void about();
<<<<<<< HEAD
};
=======
};
>>>>>>> bd0649b (init)
