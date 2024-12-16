#pragma once

#include <QWidget>
#include <QtCharts/QChartView>
#include <QtCharts/QPieSeries>

#include "../data/dataset.hpp"
#include "../window.hpp"
#include "card.hpp"

class LitterPage : public QWidget {
  Q_OBJECT

 public:
  LitterPage(WaterQalWindow* window, QWidget* parent = nullptr);
  void update(WaterQalDataset* model);
  OverviewCard* getCard() const { return card; }

 private:
  void showTooltip(QPieSlice* slice);
  QPieSeries* locationSeries;
  QPieSeries* waterBodySeries;
  OverviewCard* card;
};
