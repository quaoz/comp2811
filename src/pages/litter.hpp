#pragma once

#include <QTCharts/QChartView>
#include <QTCharts/QPieSeries>
#include <QWidget>

#include "../data/model.hpp"

class QTableView;

class LitterPage : public QWidget {
  Q_OBJECT

 public:
  LitterPage(QWidget* parent = nullptr);
  void update(QuakeModel* model);

 private:
  QChartView* chartView;
  QPieSeries* series;
};
