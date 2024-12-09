#pragma once

#include <QFrame>
#include <QGridLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QPushButton>
#include <QTabWidget>
#include <QTableView>
#include <QVBoxLayout>
#include <QWidget>
#include <QtCharts/QChartView>
#include <QtCharts/QPieSeries>
#include <QtWidgets>

#include "../data/model.hpp"

class overviewCard : public QFrame {
 public:
  overviewCard(const QString& title, QTabWidget& tabWidget,
               QWidget* parent = nullptr);
  // overviewCard(const QString& title, QWidget* parent = nullptr);
  void updateCard(QuakeModel* model, std::string cardType);
  void setPCBCounter(double counter);
  // double getPCBCounter(QuakeModel* model, double PCBCounter);
  void openWindow();

 private:
  double PCBCounter;
  QLabel* PCBCounterLabel;

  QTabWidget* tabWidget;
  std::string cardTitle;
};

class QTableView;

class MainDashboardPage : public QWidget {
  Q_OBJECT

 public:
  MainDashboardPage(QWidget* parent = nullptr);
  void update(QuakeModel* model, overviewCard* PCBCard,
              overviewCard* litterCard, overviewCard* fluoroCard);
  // void update(QuakeModel* model, overviewCard* PCBCard);

 private:
  QVBoxLayout* mainLayout;
};
