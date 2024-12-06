#include "pops.hpp"

#include <QtWidgets>

POPsPage::POPsPage(QWidget* parent) : QWidget(parent) {
  series = new QLineSeries();

  QChart* chart = new QChart();
  chart->addSeries(series);
  chart->setTitle("PCBs");
  chart->createDefaultAxes();

  chartView = new QChartView(chart);
  chartView->setRenderHint(QPainter::Antialiasing);

  QVBoxLayout* layout = new QVBoxLayout(this);
  layout->addWidget(chartView);
  setLayout(layout);
}

void POPsPage::update(QuakeModel* model) { series->clear(); }
