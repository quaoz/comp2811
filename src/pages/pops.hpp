#pragma once

#include <QComboBox>
#include <QValueAxis>
#include <QWidget>
#include <QtCharts/QChartView>
#include <QtCharts/QDateTimeAxis>
#include <QtCharts/QLineSeries>
#include <QtCharts/QScatterSeries>

#include "../data/model.hpp"
#include "../window.hpp"
#include "card.hpp"

class POPsPage : public QWidget {
  Q_OBJECT

 public:
  POPsPage(QuakeWindow* window, QWidget* parent = nullptr);
  void update(QuakeModel* model);
  OverviewCard* getCard() const { return card; }

 private slots:
  void onComboBoxChanged();

 private:
  void filter();
  void onDataPointClicked(const QPointF& point);

  QChartView* chartView;
  QLineSeries* series;
  QScatterSeries* redSeries;
  QScatterSeries* yellowSeries;
  QScatterSeries* greenSeries;
  QDateTimeAxis* axisX;
  QValueAxis* axisY;
  QComboBox* locationComboBox;
  QComboBox* pbcsComboBox;
  QuakeModel* model;
  OverviewCard* card;
  std::set<std::string> const pcbs = {
    "PCB Con 028", "PCB Con 052", "PCB Con 101", "PCB Con 105", "PCB Con 118",
    "PCB Con 138", "PCB Con 153", "PCB Con 156", "PCB Con 180", "PCBs"};
};
