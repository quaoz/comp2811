#pragma once

#include <QDateTime>
#include <QDateTimeEdit>
#include <QGridLayout>
#include <QWidget>

#include "../data/dataset.hpp"
#include "card.hpp"

class MainDashboardPage : public QWidget {
  Q_OBJECT

 public:
  MainDashboardPage(OverviewCard* pollutantCard, OverviewCard* popsCard,
                    OverviewCard* litterCard, OverviewCard* fluorinatedCard,
                    QWidget* parent = nullptr);
  void update(WaterQalDataset* model);

 private slots:
  void onStartDateChanged(const QDateTime& dateTime);
  void onEndDateChanged(const QDateTime& dateTime);

 private:
  WaterQalDataset* model;
  QDateTimeEdit* startTime;
  QDateTimeEdit* endTime;
  bool dateTimeSelectorsInitialized;
};
