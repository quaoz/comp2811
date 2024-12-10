#include "pops.hpp"

#include <QtWidgets>

POPsPage::POPsPage(QWidget* parent) : QWidget(parent) {
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
  chart->setTitle("Persistent Organic Pollutants");

  chartView = new QChartView(chart);
  chartView->setRenderHint(QPainter::Antialiasing);

  axisX = new QDateTimeAxis;
  axisX->setFormat("MMM yyyy");
  axisX->setTitleText("Date");
  axisX->setTickCount(10);
  chartView->chart()->addAxis(axisX, Qt::AlignBottom);
  series->attachAxis(axisX);
  redSeries->attachAxis(axisX);
  yellowSeries->attachAxis(axisX);
  greenSeries->attachAxis(axisX);

  axisY = new QValueAxis;
  axisY->setTitleText("Sample Quantity");
  chartView->chart()->addAxis(axisY, Qt::AlignLeft);
  series->attachAxis(axisY);
  redSeries->attachAxis(axisY);
  yellowSeries->attachAxis(axisY);
  greenSeries->attachAxis(axisY);

  locationComboBox = new QComboBox();
  pbcsComboBox = new QComboBox();

  pbcsComboBox->addItem("All POPs");
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

void POPsPage::update(QuakeModel* model) {
  this->model = model;
  locationComboBox->clear();

  locationComboBox->addItem("All Locations");
  for (const auto& location : model->getLocations()) {
    locationComboBox->addItem(QString::fromStdString(location));
  }

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

  std::vector<Sample> samples = {};

  if (selectedCompound.toStdString() == "All POPs") {
    samples = model->getPollutantSamples(pcbs);
  } else {
    samples = model->getPollutantSamples(selectedCompound.toStdString());
  }

  for (const auto& sample : samples) {
    QDateTime dateTime =
      QDateTime::fromString(sample.getSampleDateTime().c_str(), Qt::ISODate);

    if (selectedLocation.toStdString() == "All Locations" ||
        sample.getSamplingPoint().getLabel() ==
          selectedLocation.toStdString()) {
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
  QString popupText = QString("Pollutant: %1\nValue: %2\nCompliance: %3")
                        .arg("TODO: fix diff series")
                        .arg(point.y())
                        .arg(complianceLevel);

  // Show the tooltip near the cursor
  QToolTip::showText(QCursor::pos(), popupText, this);
}