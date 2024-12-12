#include "pollutants.hpp"

#include <QLegendMarker>
#include <QtWidgets>
#include <set>

PollutantPage::PollutantPage(WaterQalWindow* window, QWidget* parent)
  : QWidget(parent) {
  card = new OverviewCard(
    tr("Pollutants Overview"),
    tr("There are a large number of chemical and physical pollutants which can "
       "be "
       "found in bodies of water. Pollutants can harm the environment and pose "
       "healthrisks."),
    "Number of locations: %1", 1, window);

  chart = new TimeSeries(tr("Pollutants Overview"), this);

  locationComboBox = new QComboBox();
  pollutantComboBox = new QComboBox();

  QHBoxLayout* options = new QHBoxLayout();
  options->addWidget(pollutantComboBox);
  options->addWidget(locationComboBox);

  QPushButton* actionButton = new QPushButton("View more", this);

  QVBoxLayout* layout = new QVBoxLayout(this);
  layout->addLayout(options);
  layout->addWidget(chart);
  layout->addWidget(actionButton);
  setLayout(layout);

  connect(pollutantComboBox, &QComboBox::currentTextChanged, this,
          &PollutantPage::onComboBoxChanged);
  connect(locationComboBox, &QComboBox::currentTextChanged, this,
          &PollutantPage::onComboBoxChanged);
  connect(actionButton, &QPushButton::clicked, card, &OverviewCard::showPopUp);
}

void PollutantPage::update(WaterQalDataset* model) {
  this->model = model;
  pollutantComboBox->clear();
  locationComboBox->clear();

  std::vector<Sample> samples = model->getSamples();
  std::set<std::string> locations;
  std::set<std::string> pollutants;
  for (const auto& sample : samples) {
    locations.insert(sample.getSamplingPoint().getLabel());
    pollutants.insert(sample.getDeterminand().getLabel());
  }

  locationComboBox->addItem("All Locations");
  for (const auto& location : locations) {
    locationComboBox->addItem(QString::fromStdString(location));
  }

  for (const auto& pollutant : pollutants) {
    pollutantComboBox->addItem(QString::fromStdString(pollutant));
  }

  card->updateCard(samples.size(), locations.size());
  filter();
}

void PollutantPage::filter() {
  QString selectedPollutant = pollutantComboBox->currentText();
  QString selectedLocation = locationComboBox->currentText();

  auto samples = model->getPollutantSamples(selectedPollutant.toStdString());
  chart->updateChart(samples, selectedLocation, selectedPollutant);
}

void PollutantPage::onComboBoxChanged() { filter(); }
