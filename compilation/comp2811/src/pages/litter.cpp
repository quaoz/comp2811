#include "litter.hpp"

#include <QtWidgets>

LitterPage::LitterPage(QWidget* parent) : QWidget(parent) {
  series = new QPieSeries();

  QChart* chart = new QChart();
  chart->addSeries(series);
  chart->setTitle("Litter Samples per Location");
  chart->legend()->setAlignment(Qt::AlignLeft);

  chartView = new QChartView(chart);
  chartView->setRenderHint(QPainter::Antialiasing);

  QVBoxLayout* layout = new QVBoxLayout(this);
  layout->addWidget(chartView);
  setLayout(layout);
}

void LitterPage::update(QuakeModel* model) {
  series->clear();

  // Count the number of litter samples per location
  std::map<std::string, int> litterCount;
  for (int i = 0; i < model->rowCount(QModelIndex()); ++i) {
    Sample sample = model->getSample(i);
    if (sample.getDeterminand().getLabel() == "BWP - O.L.") {
      litterCount[sample.getSamplingPoint().getLabel()]++;
    }
  }

  // Add data to the pie series
  for (const auto& entry : litterCount) {
    series->append(entry.first.c_str(), entry.second);
  }
}
