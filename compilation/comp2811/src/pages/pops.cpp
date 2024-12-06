#include "pops.hpp"

#include <QtWidgets>

PopsPage::PopsPage(QWidget* parent) : QWidget(parent) {
  series = new QLineSeries();

  QChart* chart = new QChart();
  chart->addSeries(series);
  chart->setTitle("PCPs");
  chart->createDefaultAxes();

  chartView = new QChartView(chart);
  chartView->setRenderHint(QPainter::Antialiasing);

  QVBoxLayout* layout = new QVBoxLayout(this);
  layout->addWidget(chartView);
  setLayout(layout);
}

void PopsPage::update(QuakeModel* model) {
  series->clear();

  double counter = 0;
  double max = 0;
  for (int i = 0; i < (model->rowCount(QModelIndex())); i++) {
    Sample SampleData = model->getSample(i);

    if (SampleData.getDeterminand().getLabel().find("PCB") != std::string::npos) {
        double result = SampleData.getResult();
        if (result > max) { max = result; }

        series->append(counter++, result);
    }
  }

  max *= 1.1;

  chartView->chart()->createDefaultAxes();
  chartView->chart()->axes(Qt::Horizontal).back()->setRange(0, series->count());
  chartView->chart()->axes(Qt::Vertical).back()->setRange(0, max);
}
