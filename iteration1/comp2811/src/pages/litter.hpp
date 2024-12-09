#pragma once

#include <QWidget>
#include <QtCharts/QChartView>
#include <QtCharts/QPieSeries>

#include "../data/model.hpp"

class LitterPage : public QWidget {
  Q_OBJECT

 public:
  LitterPage(QWidget* parent = nullptr);
  void update(QuakeModel* model);

 private:
  QPieSeries* locationSeries;
  QPieSeries* waterBodySeries;
};
