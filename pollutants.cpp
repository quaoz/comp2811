#include "pollutants.hpp"

#include <QtWidgets>

PollutantPage::PollutantPage(QWidget* parent) : QWidget(parent), model(nullptr) {
  series = new QLineSeries();
  scatterSeries = new QScatterSeries();
  QChart* chart = new QChart();
  chart->addSeries(series);
  chart->addSeries(scatterSeries);
  chart->createDefaultAxes();

  chartView = new QChartView(chart);
  chartView->setRenderHint(QPainter::Antialiasing);

  // Setting search input 
  searchInput = new QLineEdit(this);
  searchInput->setPlaceholderText("Enter Pollutant Name");
  searchButton = new QPushButton("Search", this);

  // For error message label 
  messageLabel = new QLabel(this);
  messageLabel->setStyleSheet("color: red;");
  messageLabel->setText("");
  messageLabel->setAlignment(Qt::AlignCenter);
  messageLabel->hide();

  // Create pollutant cards
  QPushButton* pollutant1Button = new QPushButton("Pollutant 1", this);
  QPushButton* pollutant2Button = new QPushButton("Pollutant 2", this);

  // Connect pollutant buttons to set the pollutant and update
  connect(pollutant1Button, &QPushButton::clicked, this, [this]() {
    currentPollutant = "Pollutant 1";
    chartView->chart()->setTitle(currentPollutant);
    if (model) update(model);
  });
  connect(pollutant2Button, &QPushButton::clicked, this, [this]() {
    currentPollutant = "Pollutant 2";
    chartView->chart()->setTitle(currentPollutant);
    if (model) update(model);
  });

   // Create layout for pollutant cards
  QHBoxLayout* pollutantCardsLayout = new QHBoxLayout();
  pollutantCardsLayout->addWidget(pollutant1Button);
  pollutantCardsLayout->addWidget(pollutant2Button);

  connect(searchButton, &QPushButton::clicked, this, &PollutantPage::onSearchSubmit);
  connect(scatterSeries, &QScatterSeries::clicked, this, &PollutantPage::onDataPointClicked);

  chart->setTitle(currentPollutant);

  QVBoxLayout* layout = new QVBoxLayout(this);

  QHBoxLayout* searchLayout = new QHBoxLayout();
  searchLayout->addWidget(searchInput);
  searchLayout->addWidget(searchButton);

  layout->addLayout(searchLayout);
  layout->addLayout(pollutantCardsLayout);
  layout->addWidget(chartView);
  layout->addWidget(messageLabel);
  setLayout(layout);
}

bool PollutantPage::update(QuakeModel* model) {
  series->clear();
  scatterSeries->clear();
  double counter = 0;
  double max = 0;
  bool found = false;

  for (int i = 0; i < (model->rowCount(QModelIndex())); i++) {
    Sample SampleData = model->getSample(i);
    if (QString::fromStdString(SampleData.getDeterminand().getLabel()) == currentPollutant) {
      found = true;
      double result = SampleData.getResult();
      QString complianceLevelValue = QString::fromStdString(SampleData.isComplianceSample());
      dataPoints.append(qMakePair(result, complianceLevelValue));
      if (result > max) { max = result; }

      series->append(counter++, result);
      counter = counter - 1;
      scatterSeries->append(counter++, result);

      // Determine color based on complianceLevelValue
      QColor pointColor;
      QString normalizedComplianceLevel = complianceLevelValue.trimmed().toLower();
      if (normalizedComplianceLevel == "false") {
          pointColor = QColor(Qt::green);  // Green for compliant
      } else {
          pointColor = QColor(Qt::red);    // Red for non-compliant
      }
      QPen pen(pointColor);
      QBrush brush(pointColor);
      scatterSeries->setMarkerShape(QScatterSeries::MarkerShapeCircle); // Optional: Custom shape
      scatterSeries->setMarkerSize(10.0); // Adjust marker size
      scatterSeries->setColor(pointColor);
    }
  }

  

  if (found){
    max *= 1.1;
    chartView->chart()->createDefaultAxes();
    chartView->chart()->axes(Qt::Horizontal).back()->setRange(0, series->count());
    chartView->chart()->axes(Qt::Vertical).back()->setRange(0, max);

  }

  return found;

  
}


void PollutantPage::onSearchSubmit() {


  currentPollutant = searchInput->text();
  chartView->chart()->setTitle(currentPollutant);
  if (update(model)){
    messageLabel->hide();
    chartView->show();
  } else {
    messageLabel->setText(QString("There is no pollutant called '%1'. Please try again.").arg(currentPollutant));
    messageLabel->show();
    chartView->hide();
  }
}

void PollutantPage::setModel(QuakeModel* quakeModel) {
    model = quakeModel;
}

void PollutantPage::onDataPointClicked(const QPointF& point) {

    QString complianceLevel = "False";
    for (const auto& dataPoint : dataPoints){
      if (qFuzzyCompare(dataPoint.first, point.y())){
        complianceLevel = dataPoint.second;
        break;
      }
    }

    QString normalizedComplianceLevel = complianceLevel.trimmed().toLower();
    QString complianceLevelValue = "";
    if (normalizedComplianceLevel == "false") {
          complianceLevelValue = "Non-Compliant";
      } else {
          complianceLevelValue = "Compliant";
      }

    // Construct popup message
    QString popupText = QString("Pollutant: %1\nValue: %2\nCompliance: %3")
                            .arg(currentPollutant)
                            .arg(point.y())
                            .arg(complianceLevelValue);

    // Show the tooltip near the cursor
    QToolTip::showText(QCursor::pos(), popupText, this);
}
