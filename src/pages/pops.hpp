#pragma once

#include <QComboBox>
#include <QWidget>

#include "../data/dataset.hpp"
#include "../window.hpp"
#include "card.hpp"
#include "timeseries.hpp"

class POPsPage : public QWidget {
  Q_OBJECT

 public:
  POPsPage(WaterQalWindow* window, QWidget* parent = nullptr);
  void update(WaterQalDataset* model);
  OverviewCard* getCard() const { return card; }

 private slots:
  void onComboBoxChanged();

 private:
  void filter();

  TimeSeries* chart;
  QComboBox* locationComboBox;
  QComboBox* pbcsComboBox;
  WaterQalDataset* model;
  OverviewCard* card;
  std::set<std::string> const pcbs = {
    "PCB Con 028", "PCB Con 052", "PCB Con 101", "PCB Con 105", "PCB Con 118",
    "PCB Con 138", "PCB Con 153", "PCB Con 156", "PCB Con 180", "PCBs"};
};
