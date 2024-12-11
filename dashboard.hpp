#pragma once

#include <QTableView>
#include <QWidget>
#include <QtWidgets>
#include <QGridLayout>
#include <QPushButton>
#include <QLabel>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QtCharts/QChartView>
#include <QtCharts/QPieSeries>
#include <QFrame>
#include <QTabWidget>

#include "../data/model.hpp"
#include "pops.hpp"

class overviewCard : public QFrame {
 public:
  overviewCard(const QString& title,const QString& description, QTabWidget& tabWidget,  QWidget* parent = nullptr);
  //overviewCard(const QString& title, QWidget* parent = nullptr);
  void updateCard(QuakeModel* model, std::string cardType);
  void setPCBCounter(double counter);
  //double getPCBCounter(QuakeModel* model, double PCBCounter);
  void openWindow();

  private:
    float meanResult;
    float PCBCounter;
    QLabel* PCBCounterLabel;
    QLabel* MeanLabel;

    QTabWidget *tabWidget;
    std::string cardTitle;



    //PopsPage* popsPage;
    //TabWidget *tabWidget;
    //QuakeModel model;


};

class QTableView;

class MainDashboardPage : public QWidget {
  Q_OBJECT

 public:
  MainDashboardPage(QWidget* parent = nullptr);
  void update(QuakeModel* model, overviewCard* PCBCard, overviewCard* litterCard, overviewCard* fluoroCard);
  //void update(QuakeModel* model, overviewCard* PCBCard);


 private:
  //QChartView* chartView;
  //QPieSeries* series;
  //QuakeModel model;
  //overviewCard* PCBCard;
  QVBoxLayout* mainLayout;

};