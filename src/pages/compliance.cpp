#include "compliance.hpp"

#include <QApplication>
#include <QComboBox>
#include <QDebug>
#include <QDir>
#include <QFile>
#include <QFileDialog>
#include <QFrame>
#include <QGridLayout>
#include <QHBoxLayout>
#include <QHeaderView>
#include <QLabel>
#include <QMessageBox>
#include <QPushButton>
#include <QString>
#include <QTableWidget>
#include <QTextStream>
#include <QTranslator>
#include <QVBoxLayout>
#include <QVector>
#include <QWidget>
#include <QtWidgets>

ComplianceDashboard::ComplianceDashboard(QWidget *parent) : QWidget(parent) {
  setupUI();
}

void ComplianceDashboard::setupUI() {
  // Header Section
  QHBoxLayout *headerLayout = new QHBoxLayout();
  QLabel *appTitle = new QLabel(tr("Water Quality Monitor"), this);
  appTitle->setStyleSheet("font-size: 24px; font-weight: bold;");

  QPushButton *homeButton = new QPushButton(tr("Home"), this);
  QPushButton *pollutantsButton =
    new QPushButton(tr("Pollutants Overview"), this);
  QPushButton *complianceButton =
    new QPushButton(tr("Compliance Dashboard"), this);

  languageSelector = new QComboBox(this);
  languageSelector->addItem(tr("English", "en"));
  languageSelector->addItem(tr("French", "fr"));
  languageSelector->addItem(tr("German", "de"));

  connect(languageSelector, &QComboBox::currentTextChanged, this,
          &ComplianceDashboard::changeLanguage);

  headerLayout->addWidget(appTitle);
  headerLayout->addStretch();
  headerLayout->addWidget(homeButton);
  headerLayout->addWidget(pollutantsButton);
  headerLayout->addWidget(complianceButton);
  headerLayout->addWidget(languageSelector);

  // Filters Section
  QHBoxLayout *filterLayout = new QHBoxLayout();
  QLabel *filterLabel = new QLabel(tr("Filters:"));
  locationFilter = new QComboBox(this);
  pollutantFilter = new QComboBox(this);
  timeRangeFilter = new QComboBox(this);
  colorFilter = new QComboBox(this);

  locationFilter->addItem(tr("All Locations"));
  pollutantFilter->addItem(tr("All Pollutants"));
  timeRangeFilter->addItem(tr("Last Month"));
  timeRangeFilter->addItem(tr("Last Year"));
  colorFilter->addItem(tr("All Statuses"));  // Default filter for colors
  colorFilter->addItem(tr("Compliant"));
  colorFilter->addItem(tr("Non-Compliant"));
  colorFilter->addItem(tr("Near Limit"));

  connect(locationFilter, &QComboBox::currentTextChanged, this,
          &ComplianceDashboard::filterComplianceData);
  connect(pollutantFilter, &QComboBox::currentTextChanged, this,
          &ComplianceDashboard::filterComplianceData);
  connect(timeRangeFilter, &QComboBox::currentTextChanged, this,
          &ComplianceDashboard::filterComplianceData);
  connect(colorFilter, &QComboBox::currentTextChanged, this,
          &ComplianceDashboard::filterComplianceData);  // Connect color filter

  filterLayout->addWidget(filterLabel);
  filterLayout->addWidget(locationFilter);
  filterLayout->addWidget(pollutantFilter);
  filterLayout->addWidget(timeRangeFilter);
  filterLayout->addWidget(colorFilter);  // Add to filter layout

  // Summary Cards Section
  QLabel *summaryLabel = new QLabel(tr("Compliance Overview:"));
  summaryCardsLayout = new QGridLayout();

  // Compliance Table Section
  complianceTable = new QTableWidget(this);
  complianceTable->setColumnCount(4);
  complianceTable->setHorizontalHeaderLabels(
    {"Location", "Pollutant", "Compliance Status", "Details"});
  complianceTable->horizontalHeader()->setSectionResizeMode(
    QHeaderView::Stretch);
  connect(complianceTable, &QTableWidget::cellClicked, this,
          &ComplianceDashboard::showDetails);

  // Non-Compliant Summary Section
  nonCompliantSummary =
    new QLabel(tr("Summary of Non-Compliant Sites: None"), this);
  nonCompliantSummary->setStyleSheet("font-weight: bold; margin-top: 10px;");

  // Export and Report Buttons
  QHBoxLayout *buttonLayout = new QHBoxLayout();
  exportButton = new QPushButton(tr("Export to CSV"), this);
  generateReportButton = new QPushButton(tr("Generate Report"), this);
  buttonLayout->addWidget(exportButton);
  buttonLayout->addWidget(generateReportButton);

  connect(exportButton, &QPushButton::clicked, this,
          &ComplianceDashboard::exportToCSV);
  connect(generateReportButton, &QPushButton::clicked, this,
          &ComplianceDashboard::generateReport);

  // Footer Section
  QLabel *footerLabel = new QLabel(
    tr("Help & Resources: [User Guide] [Credits] [Data Sources]"), this);

  // Layout Setup
  mainLayout = new QVBoxLayout(this);
  mainLayout->addLayout(headerLayout);
  mainLayout->addLayout(filterLayout);
  mainLayout->addWidget(summaryLabel);
  mainLayout->addLayout(summaryCardsLayout);
  mainLayout->addWidget(complianceTable);
  mainLayout->addWidget(
    nonCompliantSummary);  // Add the non-compliant summary here
  mainLayout->addLayout(buttonLayout);
  mainLayout->addWidget(footerLabel);
  setLayout(mainLayout);
}

void ComplianceDashboard::update(QuakeModel *model) {
  this->model = model;
  locationFilter->clear();
  pollutantFilter->clear();

  for (const auto &location : model->getLocations()) {
    locationFilter->addItem(QString::fromStdString(location));
  }
  locationFilter->addItem(tr("All Locations"));

  // pollutantFilter->addItem("All Pollutants");
  for (const auto &pollutants : model->getPollutants()) {
    pollutantFilter->addItem(QString::fromStdString(pollutants));
  }
  pollutantFilter->addItem(tr("All Pollutants"));

  filterComplianceData();
}

void ComplianceDashboard::filterComplianceData() {
  QString selectedLocation = locationFilter->currentText();
  QString selectedPollutant = pollutantFilter->currentText();
  QString selectedColor = colorFilter->currentText();

  complianceTable->setRowCount(0);
  int nonCompliantCount = 0;        // Counter for non-compliant sites
  QStringList nonCompliantDetails;  // List to store non-compliant site details
  QString options[3] = {tr("Compliant"), tr("Non-Compliant"), tr("Near Limit")};

  std::vector<Sample> samples = {};

  if (selectedPollutant.toStdString() != "All Pollutants") {
    samples = model->getPollutantSamples(selectedPollutant.toStdString());
  } else {
    if (selectedLocation.toStdString() != "All Locations") {
      samples = model->getLocationSamples(selectedLocation.toStdString());
    } else {
      // TODO: handle other case
    }
  }

  for (const auto &sample : samples) {
    if ((selectedLocation == "All Locations" ||
         sample.getSamplingPoint().getLabel() ==
           selectedLocation.toStdString()) &&
        (selectedPollutant == "All Pollutants" ||
         sample.getDeterminand().getLabel() ==
           selectedPollutant.toStdString())) {
      // Apply color filter
      QString status = options[rand() % 3];
      ;
      bool matchesColor = false;
      if (selectedColor == "All Statuses") {
        matchesColor = true;
      } else if (selectedColor == "Compliant" && status == "Compliant") {
        matchesColor = true;
      } else if (selectedColor == "Non-Compliant" &&
                 status == "Non-Compliant") {
        matchesColor = true;
      } else if (selectedColor == "Near Limit" && status == "Near Limit") {
        matchesColor = true;
      }

      if (!matchesColor) {
        continue;  // Skip rows that don't match the color filter
      }

      int row = complianceTable->rowCount();
      complianceTable->insertRow(row);

      complianceTable->setItem(
        row, 0,
        new QTableWidgetItem(sample.getSamplingPoint().getLabel().c_str()));
      complianceTable->setItem(
        row, 1,
        new QTableWidgetItem(sample.getDeterminand().getLabel().c_str()));

      QTableWidgetItem *statusItem = new QTableWidgetItem(status);
      if (status == "Compliant") {
        statusItem->setBackground(Qt::green);
      } else if (status == "Non-Compliant") {
        statusItem->setBackground(Qt::red);
        nonCompliantCount++;  // Increment non-compliant counter
        nonCompliantDetails.append((sample.getSamplingPoint().getLabel() +
                                    " - " + sample.getDeterminand().getLabel())
                                     .c_str());
      } else if (status == "Near Limit") {
        statusItem->setBackground(Qt::yellow);
      }
      complianceTable->setItem(row, 2, statusItem);

      complianceTable->setItem(row, 3, new QTableWidgetItem(tr("Details")));
    }
  }

  // Update the non-compliant summary label
  if (nonCompliantCount > 0) {
    QString summaryText =
      tr("Summary of Non-Compliant Sites: %1 site(s)\nDetails:\n%2")
        .arg(nonCompliantCount)
        .arg(nonCompliantDetails.join("\n"));
    nonCompliantSummary->setText(summaryText);
  } else {
    nonCompliantSummary->setText(tr("Summary of Non-Compliant Sites: None"));
  }
}

void ComplianceDashboard::showDetails(int row) {
  QString location = complianceTable->item(row, 0)->text();
  QString pollutant = complianceTable->item(row, 1)->text();
  QString status = complianceTable->item(row, 2)->text();

  QMessageBox::information(this, tr("Details"),
                           tr("Location: %1\nPollutant: %2\nStatus: %3")
                             .arg(location, pollutant, status));
}

void ComplianceDashboard::changeLanguage(const QString &language) {
  if (translator.load(":/translations_" + language)) {
    QApplication::installTranslator(&translator);
  } else {
    QMessageBox::warning(this, tr("Language Error"),
                         tr("Failed to load language: %1").arg(language));
  }
}

void ComplianceDashboard::exportToCSV() {
  QMessageBox::information(this, tr("Export to CSV"),
                           tr("Export functionality not implemented yet."));
}

void ComplianceDashboard::generateReport() {
  QMessageBox::information(
    this, tr("Generate Report"),
    tr("Report generation functionality not implemented yet."));
}
