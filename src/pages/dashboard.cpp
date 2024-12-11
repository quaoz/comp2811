#include "dashboard.hpp"

#include "card.hpp"

// TODO: card waffle, mean median + other stats, location filter
MainDashboardPage::MainDashboardPage(OverviewCard* pollutantCard,
                                     OverviewCard* popsCard,
                                     OverviewCard* litterCard,
                                     OverviewCard* fluorinatedCard,
                                     QWidget* parent)
  : QWidget(parent) {
  QGridLayout* mainLayout = new QGridLayout(this);
  mainLayout->addWidget(pollutantCard, 1, 1);
  mainLayout->addWidget(popsCard, 1, 2);
  mainLayout->addWidget(litterCard, 2, 1);
  mainLayout->addWidget(fluorinatedCard, 2, 2);

  setLayout(mainLayout);
}
