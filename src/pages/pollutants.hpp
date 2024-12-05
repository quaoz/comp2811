#pragma once

#include <QValueAxis>
#include <QWidget>
#include <QtCharts/QChartView>
#include <QtCharts/QLineSeries>

#include "../data/model.hpp"

class QTableView;

class PollutantPage : public QWidget {
  Q_OBJECT

 public:
  PollutantPage(QWidget* parent = nullptr);
  void update(QuakeModel* model);

 private:
  QChartView* chartView;
  QLineSeries* series;
};
