#include "litter.hpp"

#include <QtWidgets>
#include <vector>

LitterPage::LitterPage(WaterQalWindow* window, QWidget* parent)
  : QWidget(parent) {
  card = new OverviewCard(
    "Environmental Litter Overview",
    "Littering is the careless disposal of trash. Waste like plastics and "
    "chemicals enters rivers, lakes, and oceans, harming aquatic life and "
    "ecosystems. Some compounds that cannot decompose persist for many years, "
    "and toxic substances can contaminate groundwater, affecting drinking "
    "water and agriculture.",
    3, window);

  locationSeries = new QPieSeries();
  waterBodySeries = new QPieSeries();

  QChart* locationChart = new QChart();
  locationChart->addSeries(locationSeries);
  locationChart->setTitle(tr("Litter Samples per Location"));
  locationChart->legend()->setAlignment(Qt::AlignLeft);

  locationChart->setAnimationOptions(QChart::AnimationOption::AllAnimations);
  locationChart->setTheme(QChart::ChartThemeBlueCerulean);

  QChartView* locationChartView = new QChartView(locationChart);
  locationChartView->setRenderHint(QPainter::Antialiasing);

  QChart* waterBodyChart = new QChart();
  waterBodyChart->addSeries(waterBodySeries);
  waterBodyChart->setTitle(tr("Litter Samples per Water Body Type"));
  waterBodyChart->legend()->setAlignment(Qt::AlignLeft);

  waterBodyChart->setAnimationOptions(QChart::AnimationOption::AllAnimations);
  waterBodyChart->setTheme(QChart::ChartThemeBlueCerulean);

  QChartView* waterBodyChartView = new QChartView(waterBodyChart);
  waterBodyChartView->setRenderHint(QPainter::Antialiasing);

  QPushButton* actionButton = new QPushButton("View more", this);

  QVBoxLayout* layout = new QVBoxLayout(this);
  layout->addWidget(locationChartView);
  layout->addWidget(waterBodyChartView);
  layout->addWidget(actionButton);
  setLayout(layout);

  connect(actionButton, &QPushButton::clicked, card, &OverviewCard::showPopUp);
}

void LitterPage::update(WaterQalDataset* model) {
  locationSeries->clear();
  waterBodySeries->clear();

  int sampleCount = model->getPollutantSamples("BWP - O.L.").size();
  card->updateCard(sampleCount, 0);

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
