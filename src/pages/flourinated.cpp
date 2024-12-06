#include "flourinated.hpp"

#include <QtWidgets>

FlourinatedPage::FlourinatedPage(QWidget* parent) : QWidget(parent) {
  series = new QLineSeries();

  QChart* chart = new QChart();
  chart->addSeries(series);
  chart->setTitle("PFAS");
  chart->createDefaultAxes();

  chartView = new QChartView(chart);
  chartView->setRenderHint(QPainter::Antialiasing);

  QVBoxLayout* layout = new QVBoxLayout(this);
  layout->addWidget(chartView);
  setLayout(layout);
}

void FlourinatedPage::update(QuakeModel* model) { series->clear(); }
