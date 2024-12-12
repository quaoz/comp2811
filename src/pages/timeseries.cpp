#include "timeseries.hpp"

#include <QCursor>
#include <QDateTime>
#include <QLabel>
#include <QLegendMarker>
#include <QToolTip>
#include <QVBoxLayout>

#include "../data/sample.hpp"

TimeSeries::TimeSeries(const QString& title, QWidget* parent)
  : QWidget(parent) {
  series = new QLineSeries();
  redSeries = new QScatterSeries();
  yellowSeries = new QScatterSeries();
  greenSeries = new QScatterSeries();

  QChart* chart = new QChart();
  chart->addSeries(series);
  chart->addSeries(redSeries);
  chart->addSeries(yellowSeries);
  chart->addSeries(greenSeries);
  chart->setTitle(title);

  chart->legend()->setVisible(true);
  chart->legend()->setAlignment(Qt::AlignBottom);
  chart->legend()->markers()[0]->setLabel("Sample Data");
  chart->legend()->markers()[1]->setLabel("Above Limit");
  chart->legend()->markers()[2]->setLabel("Near Limit");
  chart->legend()->markers()[3]->setLabel("Below Limit");

  chart->setAnimationOptions(QChart::AnimationOption::AllAnimations);
  chart->setTheme(QChart::ChartThemeBlueCerulean);

  redSeries->setBrush(QColor(255, 16, 16));
  redSeries->setMarkerShape(QScatterSeries::MarkerShapeCircle);
  redSeries->setMarkerSize(10.0);

  yellowSeries->setBrush(QColor(255, 128, 64));
  yellowSeries->setMarkerShape(QScatterSeries::MarkerShapeCircle);
  yellowSeries->setMarkerSize(10.0);

  greenSeries->setBrush(QColor(32, 192, 32));
  greenSeries->setMarkerShape(QScatterSeries::MarkerShapeCircle);
  greenSeries->setMarkerSize(10.0);

  chartView = new QChartView(chart);
  chartView->setRenderHint(QPainter::Antialiasing);

  axisX = new QDateTimeAxis;
  axisX->setFormat("dd MMM");
  axisX->setTitleText("Date");
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

  QLabel* dataPointHint = new QLabel("Click on a datapoint for more info.");

  QVBoxLayout* layout = new QVBoxLayout(this);
  layout->addWidget(chartView);
  layout->addWidget(dataPointHint);
  setLayout(layout);

  connect(redSeries, &QScatterSeries::clicked, this,
          &TimeSeries::onDataPointClicked);
  connect(yellowSeries, &QScatterSeries::clicked, this,
          &TimeSeries::onDataPointClicked);
  connect(greenSeries, &QScatterSeries::clicked, this,
          &TimeSeries::onDataPointClicked);
}

void TimeSeries::updateChart(const std::vector<Sample>& samples,
                             const QString& selectedLocation,
                             const QString& selectedCompound) {
  series->clear();
  redSeries->clear();
  yellowSeries->clear();
  greenSeries->clear();

  chartView->chart()->setTitle(QString::fromStdString(
    selectedCompound.toStdString() + " at " + selectedLocation.toStdString()));

  double max = 0;
  double redBoundary;
  double greenBoundary;
  QDateTime minDateTime;
  QDateTime maxDateTime;
  bool firstSample = true;

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

void TimeSeries::onDataPointClicked(const QPointF& point) {
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
    QString("Date: %1\nValue: %2\nCompliance: %3")
      .arg(QDateTime::fromMSecsSinceEpoch(point.x()).toString(Qt::ISODate))
      .arg(point.y())
      .arg(complianceLevel);

  // Show the tooltip near the cursor
  QToolTip::showText(QCursor::pos(), popupText, this);
}
