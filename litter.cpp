#include "litter.hpp"
#include <QtWidgets>

LitterPage::LitterPage(QWidget* parent) : QWidget(parent) {
  // Create pie series for chart
  series = new QPieSeries();

  // Create chart and set its properties
  QChart* chart = new QChart();
  chart->addSeries(series);
  chart->setTitle("Litter Samples per Location");
  chart->legend()->setAlignment(Qt::AlignLeft);

  // Create chart view and set layout
  chartView = new QChartView(chart);
  chartView->setRenderHint(QPainter::Antialiasing);

  // Create button to show popup
  QPushButton* popupButton = new QPushButton("Show Litter Info", this);
  connect(popupButton, &QPushButton::clicked, this, &LitterPage::showPopup);

  // Create layout and add widgets
  QVBoxLayout* layout = new QVBoxLayout(this);
  layout->addWidget(chartView);
  layout->addWidget(popupButton);  // Add the popup button to the layout

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

// Method to show popup
void LitterPage::showPopup() {
  // Create and configure the popup (simple message box)
  QMessageBox* popup = new QMessageBox(this);
  popup->setWindowTitle("Litter Information");
  popup->setText("When litter enters rivers, lakes, or oceans, it can harm aquatic life and disrupt ecosystems. Non-biodegradable materials like plastic take years to break down, and as they degrade, they release toxic substances that contaminate water. This pollution also affects groundwater and drinking water sources, posing risks to human health and wildlife.");
  popup->setIcon(QMessageBox::Information);
  popup->setStandardButtons(QMessageBox::Ok);
  popup->exec();  // Show the popup
}
