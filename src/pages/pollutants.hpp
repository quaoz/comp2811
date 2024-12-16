#pragma once

#include <QComboBox>
#include <QWidget>

#include "../data/dataset.hpp"
#include "../window.hpp"
#include "card.hpp"
#include "timeseries.hpp"

class PollutantPage : public QWidget {
  Q_OBJECT

 public:
  PollutantPage(WaterQalWindow* window, QWidget* parent = nullptr);
  void update(WaterQalDataset* model);
  OverviewCard* getCard() const { return card; }

 private slots:
  void onComboBoxChanged();

 private:
  void filter();

  TimeSeries* chart;
  QComboBox* pollutantComboBox;
  QComboBox* locationComboBox;
  WaterQalDataset* model;
  OverviewCard* card;
};
