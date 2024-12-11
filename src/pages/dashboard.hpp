#pragma once

#include <QGridLayout>
#include <QWidget>

#include "card.hpp"

class MainDashboardPage : public QWidget {
  Q_OBJECT

 public:
  MainDashboardPage(OverviewCard* pollutantCard, OverviewCard* popsCard,
                    OverviewCard* litterCard, OverviewCard* fluorinatedCard,
                    QWidget* parent = nullptr);
};
