#include "pops.hpp"

#include <QLegendMarker>
#include <QtWidgets>

POPsPage::POPsPage(QuakeWindow* window, QWidget* parent) : QWidget(parent) {
  card = new OverviewCard("Persistent Organic Pollutants", 2, window);

  series = new QLineSeries();
  redSeries = new QScatterSeries();
  yellowSeries = new QScatterSeries();
  greenSeries = new QScatterSeries();

  redSeries->setBrush(Qt::red);
  redSeries->setMarkerShape(QScatterSeries::MarkerShapeCircle);
  redSeries->setMarkerSize(10.0);

  yellowSeries->setBrush(Qt::yellow);
  yellowSeries->setMarkerShape(QScatterSeries::MarkerShapeCircle);
  yellowSeries->setMarkerSize(10.0);

  greenSeries->setBrush(Qt::green);
  greenSeries->setMarkerShape(QScatterSeries::MarkerShapeCircle);
  greenSeries->setMarkerSize(10.0);

  QChart* chart = new QChart();
  chart->addSeries(series);
  chart->addSeries(redSeries);
  chart->addSeries(yellowSeries);
  chart->addSeries(greenSeries);
  chart->setTitle(tr("Persistent Organic Pollutants"));

  chart->legend()->setVisible(true);
  chart->legend()->setAlignment(Qt::AlignBottom);
  chart->legend()->markers()[0]->setLabel(tr("Sample Data"));
  chart->legend()->markers()[1]->setLabel(tr("Above Limit"));
  chart->legend()->markers()[2]->setLabel(tr("Near Limit"));
  chart->legend()->markers()[3]->setLabel(tr("Below Limit"));

  chartView = new QChartView(chart);
  chartView->setRenderHint(QPainter::Antialiasing);

  axisX = new QDateTimeAxis;
  axisX->setFormat(tr("dd MMM"));
  axisX->setTitleText(tr("Date"));
  // axisX->setTickCount(10);
  chartView->chart()->addAxis(axisX, Qt::AlignBottom);
  series->attachAxis(axisX);
  redSeries->attachAxis(axisX);
  yellowSeries->attachAxis(axisX);
  greenSeries->attachAxis(axisX);

  axisY = new QValueAxis;
  axisY->setTitleText(tr("Sample Quantity"));
  chartView->chart()->addAxis(axisY, Qt::AlignLeft);
  series->attachAxis(axisY);
  redSeries->attachAxis(axisY);
  yellowSeries->attachAxis(axisY);
  greenSeries->attachAxis(axisY);

  locationComboBox = new QComboBox();
  pbcsComboBox = new QComboBox();

  for (const auto& compound : pcbs) {
    pbcsComboBox->addItem(QString::fromStdString(compound));
  }

  QHBoxLayout* options = new QHBoxLayout();
  options->addWidget(pbcsComboBox);
  options->addWidget(locationComboBox);

  QVBoxLayout* layout = new QVBoxLayout(this);
  layout->addLayout(options);
  layout->addWidget(chartView);
  setLayout(layout);

  connect(locationComboBox, &QComboBox::currentTextChanged, this,
          &POPsPage::onComboBoxChanged);
  connect(pbcsComboBox, &QComboBox::currentTextChanged, this,
          &POPsPage::onComboBoxChanged);
  connect(redSeries, &QScatterSeries::clicked, this,
          &POPsPage::onDataPointClicked);
  connect(yellowSeries, &QScatterSeries::clicked, this,
          &POPsPage::onDataPointClicked);
  connect(greenSeries, &QScatterSeries::clicked, this,
          &POPsPage::onDataPointClicked);
}

void POPsPage::update(QuakeDataset* model) {
  this->model = model;
  locationComboBox->clear();

  locationComboBox->addItem("All Locations");
  for (const auto& location : model->getLocations()) {
    locationComboBox->addItem(QString::fromStdString(location));
  }

  int sampleCount = model->getPollutantSamples(pcbs).size();
  card->updateCard(sampleCount);

  filter();
}

void POPsPage::filter() {
  series->clear();
  redSeries->clear();
  yellowSeries->clear();
  greenSeries->clear();

  QString selectedLocation = locationComboBox->currentText();
  QString selectedCompound = pbcsComboBox->currentText();

  chartView->chart()->setTitle(QString::fromStdString(
    selectedCompound.toStdString() + " at " + selectedLocation.toStdString()));

  double max = 0;
  double redBoundary;
  double greenBoundary;
  QDateTime minDateTime;
  QDateTime maxDateTime;

  bool firstSample = true;

  auto samples = model->getPollutantSamples(selectedCompound.toStdString());

  for (const auto& sample : samples) {
    if (selectedLocation.toStdString() == "All Locations" ||
        sample.getSamplingPoint().getLabel() ==
          selectedLocation.toStdString()) {
      auto dateTime =
        QDateTime::fromString(sample.getSampleDateTime().c_str(), Qt::ISODate);
      double result = sample.getResult();
      if (result > max) { max = result; }

      if (firstSample) {
        minDateTime = dateTime;
        maxDateTime = dateTime;
        redBoundary = result * 1.1;
        greenBoundary = result * 0.9;
        firstSample = false;
      } else if (dateTime < minDateTime) {
        minDateTime = dateTime;
      } else if (dateTime > maxDateTime) {
        maxDateTime = dateTime;
      }

      series->append(dateTime.toMSecsSinceEpoch(), result);

      if (result > redBoundary) {
        redSeries->append(dateTime.toMSecsSinceEpoch(), result);
      } else if (result < greenBoundary) {
        greenSeries->append(dateTime.toMSecsSinceEpoch(), result);
      } else {
        yellowSeries->append(dateTime.toMSecsSinceEpoch(), result);
      }
    }
  }

  max *= 1.05;

  axisX->setRange(minDateTime, maxDateTime);
  axisX->setTickCount(maxDateTime.date().month() - minDateTime.date().month());
  axisY->setRange(0, max);
}

void POPsPage::onComboBoxChanged() { filter(); }

void POPsPage::onDataPointClicked(const QPointF& point) {
  QString complianceLevel;

  if (redSeries->points().contains(point)) {
    complianceLevel = "Not Compliant";
  } else if (yellowSeries->points().contains(point)) {
    complianceLevel = "Near Limit";
  } else if (greenSeries->points().contains(point)) {
    complianceLevel = "Compliant";
  } else {
    complianceLevel = "Unknown";
  }

  // Construct popup message
  QString popupText =
    QString(tr("Pollutant: %1\nDate: %2\nValue: %3\nCompliance: %4"))
      .arg(pbcsComboBox->currentText())
      .arg(QDateTime::fromMSecsSinceEpoch(point.x()).toString(Qt::ISODate))
      .arg(point.y())
      .arg(complianceLevel);

  // Show the tooltip near the cursor
  QToolTip::showText(QCursor::pos(), popupText, this);
}
