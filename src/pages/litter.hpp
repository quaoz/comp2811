#pragma once

#include <QWidget>
#include <QtCharts/QChartView>
#include <QtCharts/QPieSeries>

#include "../data/model.hpp"
#include "../window.hpp"
#include "card.hpp"

class LitterPage : public QWidget {
  Q_OBJECT

 public:
  LitterPage(QuakeWindow* window, QWidget* parent = nullptr);
  void update(QuakeModel* model);
  OverviewCard* getCard() const { return card; }

 private:
  QPieSeries* locationSeries;
  QPieSeries* waterBodySeries;
  OverviewCard* card;
};
