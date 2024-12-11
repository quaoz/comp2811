#pragma once

#include <QWidget>
#include <QtCharts/QChartView>
#include <QtCharts/QDateTimeAxis>
#include <QtCharts/QLineSeries>
#include <QtCharts/QScatterSeries>
#include <QtCharts/QValueAxis>

#include "../data/sample.hpp"

class TimeSeries : public QWidget {
  Q_OBJECT

 public:
  TimeSeries(const QString& title, QWidget* parent = nullptr);
  void updateChart(const std::vector<Sample>& samples,
                   const QString& selectedLocation,
                   const QString& selectedCompound);

 private:
  void onDataPointClicked(const QPointF& point);

  QChartView* chartView;
  QLineSeries* series;
  QScatterSeries* redSeries;
  QScatterSeries* yellowSeries;
  QScatterSeries* greenSeries;
  QDateTimeAxis* axisX;
  QValueAxis* axisY;
};
