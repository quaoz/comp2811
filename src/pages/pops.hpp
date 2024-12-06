#pragma once

#include <QValueAxis>
#include <QWidget>
#include <QtCharts/QChartView>
#include <QtCharts/QLineSeries>

#include "../data/model.hpp"

class POPsPage : public QWidget {
  Q_OBJECT

 public:
  POPsPage(QWidget* parent = nullptr);
  void update(QuakeModel* model);

 private:
  QChartView* chartView;
  QLineSeries* series;
};
