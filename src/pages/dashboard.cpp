#include "dashboard.hpp"

#include <QHBoxLayout>
#include <QVBoxLayout>
#include <iostream>

#include "card.hpp"

// TODO: card waffle, mean median + other stats, location filter
MainDashboardPage::MainDashboardPage(OverviewCard* pollutantCard,
                                     OverviewCard* popsCard,
                                     OverviewCard* litterCard,
                                     OverviewCard* fluorinatedCard,
                                     QWidget* parent)
  : QWidget(parent), dateTimeSelectorsInitialized(false) {
  startTime = new QDateTimeEdit();
  endTime = new QDateTimeEdit();
  startTime->setCalendarPopup(true);
  endTime->setCalendarPopup(true);

  QHBoxLayout* dateSelectors = new QHBoxLayout();
  dateSelectors->addWidget(startTime);
  dateSelectors->addWidget(endTime);

  QWidget* dates = new QWidget(this);
  dates->setLayout(dateSelectors);

  QGridLayout* layout = new QGridLayout();
  layout->addWidget(pollutantCard, 1, 1);
  layout->addWidget(popsCard, 1, 2);
  layout->addWidget(litterCard, 2, 1);
  layout->addWidget(fluorinatedCard, 2, 2);

  QWidget* cards = new QWidget(this);
  cards->setLayout(layout);

  QVBoxLayout* mainLayout = new QVBoxLayout(this);
  mainLayout->addWidget(dates);
  mainLayout->addWidget(cards);

  setLayout(mainLayout);

  connect(startTime, &QDateTimeEdit::dateTimeChanged, this,
          &MainDashboardPage::onStartDateChanged);
  connect(endTime, &QDateTimeEdit::dateTimeChanged, this,
          &MainDashboardPage::onEndDateChanged);
}

void MainDashboardPage::update(WaterQalDataset* model) {
  this->model = model;

  if (model->size() != 0 && !dateTimeSelectorsInitialized) {
    auto minDate = QDateTime::fromString(
      model->at(model->size() - 1).getSampleDateTime().c_str(), Qt::ISODate);
    auto maxDate = QDateTime::fromString(
      model->at(0).getSampleDateTime().c_str(), Qt::ISODate);

    std::cout << "min: " << minDate.toString().toStdString() << "\n";
    std::cout << "max: " << maxDate.toString().toStdString() << "\n";

    startTime->setDateTimeRange(minDate, maxDate);
    endTime->setDateTimeRange(minDate, maxDate);
    startTime->setDateTime(minDate);
    endTime->setDateTime(maxDate);

    dateTimeSelectorsInitialized = true;
  }
}

void MainDashboardPage::onStartDateChanged(const QDateTime& dateTime) {
  if (model) {
    model->setDataMask(dateTime.toString(Qt::ISODate).toStdString(),
                       endTime->dateTime().toString(Qt::ISODate).toStdString());
    emit model->dataChanged();
  }
}

void MainDashboardPage::onEndDateChanged(const QDateTime& dateTime) {
  if (model) {
    model->setDataMask(
      startTime->dateTime().toString(Qt::ISODate).toStdString(),
      dateTime.toString(Qt::ISODate).toStdString());
    emit model->dataChanged();
  }
}
