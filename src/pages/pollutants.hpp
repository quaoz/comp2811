#pragma once

#include <QComboBox>
#include <QValueAxis>
#include <QWidget>
#include <QtCharts/QChartView>
#include <QtCharts/QDateTimeAxis>
#include <QtCharts/QLineSeries>
#include <QtCharts/QScatterSeries>

#include "../data/model.hpp"

class QTableView;

class PollutantPage : public QWidget {
  Q_OBJECT

 public:
  PollutantPage(QWidget* parent = nullptr);
  void update(QuakeModel* model);

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
  QComboBox* pollutantComboBox;
  QComboBox* locationComboBox;
  QuakeModel* model;
};
