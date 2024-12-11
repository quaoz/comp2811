#include "fluorinated.hpp"

#include <QLegendMarker>
#include <QtWidgets>

FluorinatedPage::FluorinatedPage(WaterQalWindow* window, QWidget* parent)
  : QWidget(parent) {
  card = new OverviewCard(
    tr("Fluorinated Compounds Overview"),
    tr("Fluorinated compounds are chemicals containing fluorine atoms that are "
    "highly stable and resistant to degradation. These compounds are used in "
    "various products like non-stick coatings and fire-fighting foams, but "
    "they persist in the environment and can contaminate water, soil, and "
    "wildlife, posing health risks."),
    4, window);

  chart = new TimeSeries(tr("Fluorinated Compounds"), this);

  locationComboBox = new QComboBox();
  fluorinatedComboBox = new QComboBox();

  for (const auto& compound : fluorinatedCompounds) {
    fluorinatedComboBox->addItem(QString::fromStdString(compound));
  }

  QHBoxLayout* options = new QHBoxLayout();
  options->addWidget(fluorinatedComboBox);
  options->addWidget(locationComboBox);

  QPushButton* actionButton = new QPushButton(tr("View more"), this);

  QVBoxLayout* layout = new QVBoxLayout(this);
  layout->addLayout(options);
  layout->addWidget(chart);
  layout->addWidget(actionButton);
  setLayout(layout);

  connect(locationComboBox, &QComboBox::currentTextChanged, this,
          &FluorinatedPage::onComboBoxChanged);
  connect(fluorinatedComboBox, &QComboBox::currentTextChanged, this,
          &FluorinatedPage::onComboBoxChanged);
  connect(actionButton, &QPushButton::clicked, card, &OverviewCard::showPopUp);
}

void FluorinatedPage::update(WaterQalDataset* model) {
  this->model = model;
  locationComboBox->clear();

  locationComboBox->addItem(tr("All Locations"));
  for (const auto& location : model->getLocations()) {
    locationComboBox->addItem(QString::fromStdString(location));
  }

  int sampleCount = model->getPollutantSamples(fluorinatedCompounds).size();
  card->updateCard(sampleCount, 0);

  filter();
}

void FluorinatedPage::filter() {
  QString selectedLocation = locationComboBox->currentText();
  QString selectedCompound = fluorinatedComboBox->currentText();

  auto samples = model->getPollutantSamples(selectedCompound.toStdString());
  chart->updateChart(samples, selectedLocation, selectedCompound);
}

void FluorinatedPage::onComboBoxChanged() { filter(); }
