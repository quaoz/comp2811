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
    "Number of locations: %1", 3, window);

  locationSeries = new QPieSeries();
  waterBodySeries = new QPieSeries();

  QChart* locationChart = new QChart();
  locationChart->addSeries(locationSeries);
  locationChart->setTitle(tr("Litter Samples per Location"));
  locationChart->legend()->setAlignment(Qt::AlignLeft);

  locationChart->setAnimationOptions(QChart::AnimationOption::AllAnimations);
  locationChart->setTheme(QChart::ChartThemeBlueCerulean);
  locationChart->setMinimumHeight(600);

  QChartView* locationChartView = new QChartView(locationChart);
  locationChartView->setRenderHint(QPainter::Antialiasing);

  QChart* waterBodyChart = new QChart();
  waterBodyChart->addSeries(waterBodySeries);
  waterBodyChart->setTitle(tr("Litter Samples per Water Body Type"));
  waterBodyChart->legend()->setAlignment(Qt::AlignLeft);

  waterBodyChart->setAnimationOptions(QChart::AnimationOption::AllAnimations);
  waterBodyChart->setTheme(QChart::ChartThemeBlueCerulean);
  waterBodyChart->setMinimumHeight(600);

  QChartView* waterBodyChartView = new QChartView(waterBodyChart);
  waterBodyChartView->setRenderHint(QPainter::Antialiasing);

  QScrollArea* locationScrollArea = new QScrollArea(this);
  locationScrollArea->setWidget(locationChartView);
  locationScrollArea->setWidgetResizable(true);
  locationScrollArea->setMinimumHeight(300);

  QScrollArea* waterBodyScrollArea = new QScrollArea(this);
  waterBodyScrollArea->setWidget(waterBodyChartView);
  waterBodyScrollArea->setWidgetResizable(true);
  waterBodyScrollArea->setMinimumHeight(300);

  QPushButton* actionButton = new QPushButton("View more", this);

  QWidget* charts = new QWidget(this);
  QHBoxLayout* chartLayout = new QHBoxLayout(charts);
  chartLayout->addWidget(locationScrollArea);
  chartLayout->addWidget(waterBodyScrollArea);
  charts->setLayout(chartLayout);

  QVBoxLayout* layout = new QVBoxLayout(this);
  layout->addWidget(charts);
  layout->addWidget(actionButton);
  setLayout(layout);

  connect(actionButton, &QPushButton::clicked, card, &OverviewCard::showPopUp);
  connect(locationSeries, &QPieSeries::hovered, this, &LitterPage::showTooltip);
  connect(waterBodySeries, &QPieSeries::hovered, this,
          &LitterPage::showTooltip);
}

void LitterPage::update(WaterQalDataset* model) {
  locationSeries->clear();
  waterBodySeries->clear();

  auto samples = model->getPollutantSamples("BWP - O.L.");

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

  card->updateCard(samples.size(), locationSeries->slices().size());
}

void LitterPage::showTooltip(QPieSlice* slice) {
  QToolTip::showText(QCursor::pos(),
                     QString("%1: %2").arg(slice->label()).arg(slice->value()),
                     this);
}
