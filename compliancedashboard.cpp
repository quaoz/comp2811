#include "compliancedashboard.hpp"
#include <QFile>
#include <QFileDialog>
#include <QTextStream>
#include <QMessageBox>
#include <QApplication>
#include <QDebug>
#include <QDir>
#include <QHeaderView>
#include <QtWidgets>

// ComplianceDashboard::ComplianceDashboard(QWidget *parent) : QWidget(parent) {
//     //setupUI();
//     addFileMenu();
//     loadComplianceData();
//     filterComplianceData(); // Populate the table on initialization
// }

ComplianceDashboard::ComplianceDashboard() : QMainWindow() {
    addFileMenu();
    loadComplianceData();
    filterComplianceData(); // Populate the table on initialization
}

void ComplianceDashboard::addFileMenu() {
  QAction* locAction = new QAction("Set Data &Location", this);
  locAction->setShortcut(QKeySequence(Qt::CTRL | Qt::Key_L));
  connect(locAction, SIGNAL(triggered()), this, SLOT(setDataLocation()));

  QAction* closeAction = new QAction("Quit", this);
  closeAction->setShortcut(QKeySequence::Close);
  connect(closeAction, SIGNAL(triggered()), this, SLOT(close()));

  QMenu* fileMenu = menuBar()->addMenu("&File");
  fileMenu->addAction(locAction);
  fileMenu->addAction(closeAction);
}

void ComplianceDashboard::setupUI() {


    // Header Section
    QHBoxLayout *headerLayout = new QHBoxLayout();
    QLabel *appTitle = new QLabel(tr("Water Quality Monitor"), this);
    appTitle->setStyleSheet("font-size: 24px; font-weight: bold;");

    QPushButton *homeButton = new QPushButton(tr("Home"), this);
    QPushButton *pollutantsButton = new QPushButton(tr("Pollutants Overview"), this);
    QPushButton *complianceButton = new QPushButton(tr("Compliance Dashboard"), this);

    languageSelector = new QComboBox(this);
    languageSelector->addItem("English", "en");
    languageSelector->addItem("French", "fr");
    languageSelector->addItem("German", "de");

    connect(languageSelector, &QComboBox::currentTextChanged, this, &ComplianceDashboard::changeLanguage);

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

    locationFilter->addItem("All Locations");
    pollutantFilter->addItem("All Pollutants");
    timeRangeFilter->addItem("Last Month");
    timeRangeFilter->addItem("Last Year");
    colorFilter->addItem("All Statuses"); // Default filter for colors
    colorFilter->addItem("Compliant");
    colorFilter->addItem("Non-Compliant");
    colorFilter->addItem("Near Limit");

    connect(locationFilter, &QComboBox::currentTextChanged, this, &ComplianceDashboard::filterComplianceData);
    connect(pollutantFilter, &QComboBox::currentTextChanged, this, &ComplianceDashboard::filterComplianceData);
    connect(timeRangeFilter, &QComboBox::currentTextChanged, this, &ComplianceDashboard::filterComplianceData);
    connect(colorFilter, &QComboBox::currentTextChanged, this, &ComplianceDashboard::filterComplianceData); // Connect color filter


    filterLayout->addWidget(filterLabel);
    filterLayout->addWidget(locationFilter);
    filterLayout->addWidget(pollutantFilter);
    filterLayout->addWidget(timeRangeFilter);
    filterLayout->addWidget(colorFilter); // Add to filter layout


    // Summary Cards Section
    QLabel *summaryLabel = new QLabel(tr("Compliance Overview:"));
    summaryCardsLayout = new QGridLayout();

    // Compliance Table Section
    complianceTable = new QTableWidget(this);
    complianceTable->setColumnCount(4);
    complianceTable->setHorizontalHeaderLabels({"Location", "Pollutant", "Compliance Status", "Details"});
    complianceTable->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    connect(complianceTable, &QTableWidget::cellClicked, this, &ComplianceDashboard::showDetails);

    // Non-Compliant Summary Section
    nonCompliantSummary = new QLabel(tr("Summary of Non-Compliant Sites: None"), this);
    nonCompliantSummary->setStyleSheet("font-weight: bold; margin-top: 10px;");

    // Export and Report Buttons
    QHBoxLayout *buttonLayout = new QHBoxLayout();
    exportButton = new QPushButton(tr("Export to CSV"), this);
    generateReportButton = new QPushButton(tr("Generate Report"), this);
    buttonLayout->addWidget(exportButton);
    buttonLayout->addWidget(generateReportButton);

    connect(exportButton, &QPushButton::clicked, this, &ComplianceDashboard::exportToCSV);
    connect(generateReportButton, &QPushButton::clicked, this, &ComplianceDashboard::generateReport);

    // Footer Section
    QLabel *footerLabel = new QLabel(tr("Help & Resources: [User Guide] [Credits] [Data Sources]"), this);

    // Layout Setup
    mainLayout = new QVBoxLayout(this);
    mainLayout->addLayout(headerLayout);
    mainLayout->addLayout(filterLayout);
    mainLayout->addWidget(summaryLabel);
    mainLayout->addLayout(summaryCardsLayout);
    mainLayout->addWidget(complianceTable);
    mainLayout->addWidget(nonCompliantSummary); // Add the non-compliant summary here
    mainLayout->addLayout(buttonLayout);
    mainLayout->addWidget(footerLabel);
    setLayout(mainLayout);
}

void ComplianceDashboard::loadComplianceData() {
    QString filePath = QFileDialog::getOpenFileName(this, tr("Open CSV File"), QDir::currentPath(), tr("CSV Files (*.csv)"));
    if (filePath.isEmpty()) {
        QMessageBox::information(this, tr("No File Selected"), tr("Please select a CSV file to load data."));
        return;
    }

    QFile file(filePath);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QMessageBox::critical(this, tr("Error"), tr("Unable to open file: %1").arg(filePath));
        return;
    }

    complianceDataset.clear();
    locationFilter->clear();
    pollutantFilter->clear();

    QTextStream in(&file);
    QString headerLine = in.readLine(); // Skip the header line

    while (!in.atEnd()) {
        QString line = in.readLine();
        QStringList fields = line.split(',');

        if (fields.size() == 3) {
            ComplianceData data = {fields[0].trimmed(), fields[1].trimmed(), fields[2].trimmed()};
            complianceDataset.append(data);
        }
    }

    file.close();

    // Populate filters dynamically
    QSet<QString> locations, pollutants;
    for (const auto &data : complianceDataset) {
        locations.insert(data.location);
        pollutants.insert(data.pollutant);
    }

    QStringList locationList = {"All Locations"};
    locationList.append(locations.values());
    locationFilter->addItems(locationList);

    QStringList pollutantList = {"All Pollutants"};
    pollutantList.append(pollutants.values());
    pollutantFilter->addItems(pollutantList);

    filterComplianceData();
}

void ComplianceDashboard::filterComplianceData() {
    QString selectedLocation = locationFilter->currentText();
    QString selectedPollutant = pollutantFilter->currentText();
    QString selectedColor = colorFilter->currentText();

    complianceTable->setRowCount(0);
    int nonCompliantCount = 0; // Counter for non-compliant sites
    QStringList nonCompliantDetails; // List to store non-compliant site details

    for (const auto &data : complianceDataset) {
        if ((selectedLocation == "All Locations" || data.location == selectedLocation) &&
            (selectedPollutant == "All Pollutants" || data.pollutant == selectedPollutant)) {
            
            // Apply color filter
            bool matchesColor = false;
            if (selectedColor == "All Statuses") {
                matchesColor = true;
            } else if (selectedColor == "Compliant" && data.status == "Compliant") {
                matchesColor = true;
            } else if (selectedColor == "Non-Compliant" && data.status == "Non-Compliant") {
                matchesColor = true;
            } else if (selectedColor == "Near Limit" && data.status == "Near Limit") {
                matchesColor = true;
            }

            if (!matchesColor) {
                continue; // Skip rows that don't match the color filter
            }

            int row = complianceTable->rowCount();
            complianceTable->insertRow(row);

            complianceTable->setItem(row, 0, new QTableWidgetItem(data.location));
            complianceTable->setItem(row, 1, new QTableWidgetItem(data.pollutant));

            QTableWidgetItem *statusItem = new QTableWidgetItem(data.status);
            if (data.status == "Compliant") {
                statusItem->setBackground(Qt::green);
            } else if (data.status == "Non-Compliant") {
                statusItem->setBackground(Qt::red);
                nonCompliantCount++; // Increment non-compliant counter
                nonCompliantDetails.append(data.location + " - " + data.pollutant);
            } else if (data.status == "Near Limit") {
                statusItem->setBackground(Qt::yellow);
            }
            complianceTable->setItem(row, 2, statusItem);

            complianceTable->setItem(row, 3, new QTableWidgetItem("Details"));
        }
    }

    // Update the non-compliant summary label
    if (nonCompliantCount > 0) {
        QString summaryText = tr("Summary of Non-Compliant Sites: %1 site(s)\nDetails:\n%2")
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

    QMessageBox::information(this, tr("Details"), tr("Location: %1\nPollutant: %2\nStatus: %3").arg(location, pollutant, status));
}

void ComplianceDashboard::changeLanguage(const QString &language) {
    if (translator.load(":/translations_" + language)) {
        QApplication::installTranslator(&translator);
    } else {
        QMessageBox::warning(this, tr("Language Error"), tr("Failed to load language: %1").arg(language));
    }
}

void ComplianceDashboard::exportToCSV() {
    QMessageBox::information(this, tr("Export to CSV"), tr("Export functionality not implemented yet."));
}

void ComplianceDashboard::generateReport() {
    QMessageBox::information(this, tr("Generate Report"), tr("Report generation functionality not implemented yet."));
}

void ComplianceDashboard::setDataLocation() {
  QString directory = QFileDialog::getExistingDirectory(
    this, "Data Location", ".",
    QFileDialog::ShowDirsOnly | QFileDialog::DontResolveSymlinks);

  if (directory.length() > 0) { dataLocation = directory; }
}

void ComplianceDashboard::openCSV() {
  if (dataLocation == "") {
    QMessageBox::critical(this, "Data Location Error",
                          "Data location has not been set!\n\n"
                          "You can specify this via the File menu.");
    return;
  }

  auto filename = QString("Y-%1.csv").arg(period->currentText());

  auto path = dataLocation + "/" + filename;

  try {
    model.updateFromFile(path);
  } catch (const std::exception& error) {
    QMessageBox::critical(this, "CSV File Error", error.what());
    return;
  }

  fileInfo->setText(QString("Current file: <kbd>%1</kbd>").arg(filename));
  //table->resizeColumnsToContents();

  setupUI();
}