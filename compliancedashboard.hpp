#ifndef COMPLIANCEDASHBOARD_HPP
#define COMPLIANCEDASHBOARD_HPP

#include <QWidget>
#include <QVBoxLayout>
#include <QGridLayout>
#include <QTableWidget>
#include <QComboBox>
#include <QPushButton>
#include <QLabel>
#include <QFrame>
#include <QTranslator>
#include <QHBoxLayout>
#include <QVector>
#include <QString>
#include <QMainWindow>
#include "csv.hpp"

class QMenu;

class ComplianceDashboard : public QMainWindow {
    Q_OBJECT

public:
    //explicit ComplianceDashboard(QWidget *parent = nullptr);
    ComplianceDashboard();

private slots:
    void loadComplianceData();
    void filterComplianceData();
    void showDetails(int row);
    void changeLanguage(const QString &language);
    void exportToCSV();
    void generateReport();
    void addFileMenu();

private:
    void setupUI();
    void createSummaryCard(const QString &title, const QString &status, const QString &color);

    QVBoxLayout *mainLayout;
    QGridLayout *summaryCardsLayout;
    QTableWidget *complianceTable;
    QComboBox *locationFilter;
    QComboBox *pollutantFilter;
    QComboBox *timeRangeFilter;
    QComboBox *languageSelector;
    QPushButton *exportButton;
    QPushButton *generateReportButton;
    QComboBox *colorFilter; // Filter by compliance status color
    QLabel *nonCompliantSummary; // Label to display summary of non-compliant sites

    struct ComplianceData {
        QString location;
        QString pollutant;
        QString status;
        QString concentration; // Added concentration for clarity
    };
    QVector<ComplianceData> complianceDataset;

    QTranslator translator;

private slots:
    void setDataLocation();
    void openCSV();
};

#endif // COMPLIANCEDASHBOARD_HPP
