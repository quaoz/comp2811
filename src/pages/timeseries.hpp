#pragma once

#include <QWidget>
#include <QtCharts/QChartView>
#include <QtCharts/QDateTimeAxis>
#include <QtCharts/QLineSeries>
#include <QtCharts/QScatterSeries>
#include <QtCharts/QValueAxis>

#include "../data/sample.hpp"

/**
 * A widget for displaying a time series chart
 */
class TimeSeries : public QWidget {
  Q_OBJECT

 public:
  /**
   * Constructor
   *
   * @param title   The title of the chart
   * @param parent  The parent widget
   */
  TimeSeries(const QString& title, QWidget* parent = nullptr);

  /**
   * Updates the chart with the given samples
   *
   * @param samples           The samples to display
   * @param selectedLocation  The selected location
   * @param selectedCompound  The selected compound
   */
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
