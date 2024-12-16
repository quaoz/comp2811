#include "pops.hpp"

#include <QLegendMarker>
#include <QtWidgets>
#include <set>

#include "timeseries.hpp"

POPsPage::POPsPage(WaterQalWindow* window, QWidget* parent) : QWidget(parent) {
  card = new OverviewCard(
    tr("Persistent Organic Pollutants"),
    tr("Polychlorinated biphenyls (PCBs) are a group of manmade chemical that "
       "persist in the environment and accumulate in living organisms. PCBs "
       "were used widely in electrical equipment and bind strongly to soil and "
       "sediment, causing pollution to the environment."),
    tr("Number of locations: %1"), 2, window);

  chart = new TimeSeries(tr("Persistent Organic Pollutants"));

  locationComboBox = new QComboBox();
  pbcsComboBox = new QComboBox();

  for (const auto& compound : pcbs) {
    pbcsComboBox->addItem(QString::fromStdString(compound));
  }

  QHBoxLayout* options = new QHBoxLayout();
  options->addWidget(pbcsComboBox);
  options->addWidget(locationComboBox);

  QPushButton* actionButton = new QPushButton(tr("View more"), this);

  QVBoxLayout* layout = new QVBoxLayout(this);
  layout->addLayout(options);
  layout->addWidget(chart);
  layout->addWidget(actionButton);
  setLayout(layout);

  connect(locationComboBox, &QComboBox::currentTextChanged, this,
          &POPsPage::onComboBoxChanged);
  connect(pbcsComboBox, &QComboBox::currentTextChanged, this,
          &POPsPage::onComboBoxChanged);
  connect(actionButton, &QPushButton::clicked, card, &OverviewCard::showPopUp);
}

void POPsPage::update(WaterQalDataset* model) {
  this->model = model;
  locationComboBox->clear();

  auto samples = model->getPollutantSamples(pcbs);

  std::set<std::string> locations;
  for (const auto& sample : samples) {
    locations.insert(sample.getSamplingPoint().getLabel());
  }

  locationComboBox->addItem("All Locations");
  for (const auto& location : locations) {
    locationComboBox->addItem(QString::fromStdString(location));
  }

  card->updateCard(samples.size(), locations.size());

  filter();
}

void POPsPage::filter() {
  QString selectedLocation = locationComboBox->currentText();
  QString selectedCompound = pbcsComboBox->currentText();

  auto samples = model->getPollutantSamples(selectedCompound.toStdString());
  chart->updateChart(samples, selectedLocation, selectedCompound);
}

void POPsPage::onComboBoxChanged() { filter(); }
