#include "dashboard.hpp"

#include <QHBoxLayout>
#include <QVBoxLayout>
#include <iostream>

#include "card.hpp"

MainDashboardPage::MainDashboardPage(OverviewCard* pollutantCard,
                                     OverviewCard* popsCard,
                                     OverviewCard* litterCard,
                                     OverviewCard* fluorinatedCard,
                                     QWidget* parent)
  : QWidget(parent) {
  QGridLayout* layout = new QGridLayout();
  layout->addWidget(pollutantCard, 1, 1);
  layout->addWidget(popsCard, 1, 2);
  layout->addWidget(litterCard, 2, 1);
  layout->addWidget(fluorinatedCard, 2, 2);

  QWidget* cards = new QWidget(this);
  cards->setLayout(layout);

  QVBoxLayout* mainLayout = new QVBoxLayout(this);
  mainLayout->addWidget(cards);

  setLayout(mainLayout);
}
