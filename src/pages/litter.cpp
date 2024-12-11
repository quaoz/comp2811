#include "litter.hpp"

#include <QtWidgets>
#include <vector>

LitterPage::LitterPage(QuakeWindow* window, QWidget* parent) : QWidget(parent) {
  card = new OverviewCard("Environmental Litter Overview", 3, window);

  locationSeries = new QPieSeries();
  waterBodySeries = new QPieSeries();

  QChart* locationChart = new QChart();
  locationChart->addSeries(locationSeries);
  locationChart->setTitle(tr("Litter Samples per Location"));
  locationChart->legend()->setAlignment(Qt::AlignLeft);

  QChartView* locationChartView = new QChartView(locationChart);
  locationChartView->setRenderHint(QPainter::Antialiasing);

  QChart* waterBodyChart = new QChart();
  waterBodyChart->addSeries(waterBodySeries);
  waterBodyChart->setTitle(tr("Litter Samples per Water Body Type"));
  waterBodyChart->legend()->setAlignment(Qt::AlignLeft);

  QChartView* waterBodyChartView = new QChartView(waterBodyChart);
  waterBodyChartView->setRenderHint(QPainter::Antialiasing);

  QVBoxLayout* layout = new QVBoxLayout(this);
  layout->addWidget(locationChartView);
  layout->addWidget(waterBodyChartView);
  setLayout(layout);
}

void LitterPage::update(QuakeDataset* model) {
  locationSeries->clear();
  waterBodySeries->clear();

  int sampleCount = model->getPollutantSamples("BWP - O.L.").size();
  card->updateCard(sampleCount);

  std::vector<Sample> samples = model->getPollutantSamples("BWP - O.L.");

  std::map<std::string, int> locationCount;
  std::map<std::string, int> waterBodyCount;
  for (const auto& sample : samples) {
    locationCount[sample.getSamplingPoint().getLabel()]++;
    waterBodyCount[sample.getSampledMaterialType()]++;
  }

  for (const auto& entry : locationCount) {
    locationSeries->append(entry.first.c_str(), entry.second);
  }

  for (const auto& entry : waterBodyCount) {
    waterBodySeries->append(entry.first.c_str(), entry.second);
  }
}
