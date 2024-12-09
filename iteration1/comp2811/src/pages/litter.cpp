#include "litter.hpp"

#include <QtWidgets>

LitterPage::LitterPage(QWidget* parent) : QWidget(parent) {
  locationSeries = new QPieSeries();
  waterBodySeries = new QPieSeries();

  QChart* locationChart = new QChart();
  locationChart->addSeries(locationSeries);
  locationChart->setTitle("Litter Samples per Location");
  locationChart->legend()->setAlignment(Qt::AlignLeft);

  QChartView* locationChartView = new QChartView(locationChart);
  locationChartView->setRenderHint(QPainter::Antialiasing);

  QChart* waterBodyChart = new QChart();
  waterBodyChart->addSeries(waterBodySeries);
  waterBodyChart->setTitle("Litter Samples per Water Body Type");
  waterBodyChart->legend()->setAlignment(Qt::AlignLeft);

  QChartView* waterBodyChartView = new QChartView(waterBodyChart);
  waterBodyChartView->setRenderHint(QPainter::Antialiasing);

  QVBoxLayout* layout = new QVBoxLayout(this);
  layout->addWidget(locationChartView);
  layout->addWidget(waterBodyChartView);
  setLayout(layout);
}

void LitterPage::update(QuakeModel* model) {
  locationSeries->clear();
  waterBodySeries->clear();

  std::map<std::string, int> locationCount;
  std::map<std::string, int> waterBodyCount;
  for (int i = 0; i < model->rowCount(QModelIndex()); ++i) {
    Sample sample = model->getSample(i);
    if (sample.getDeterminand().getLabel() == "BWP - O.L.") {
      locationCount[sample.getSamplingPoint().getLabel()]++;
      waterBodyCount[sample.getSampledMaterialType()]++;
    }
  }

  for (const auto& entry : locationCount) {
    locationSeries->append(entry.first.c_str(), entry.second);
  }

  for (const auto& entry : waterBodyCount) {
    waterBodySeries->append(entry.first.c_str(), entry.second);
  }
}
