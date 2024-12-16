#pragma once

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

#include "../data/dataset.hpp"

class QMenu;

class ComplianceDashboard : public QWidget {
  Q_OBJECT

 public:
  ComplianceDashboard(QWidget *parent = nullptr);
  void update(WaterQalDataset *model);

 private slots:
  void filterComplianceData();
  void showDetails(int row);

 private:
  void setupUI();
  void createSummaryCard(const QString &title, const QString &status,
                         const QString &color);

  QVBoxLayout *mainLayout;
  QGridLayout *summaryCardsLayout;
  QTableWidget *complianceTable;
  QComboBox *locationFilter;
  QComboBox *pollutantFilter;
  QComboBox *languageSelector;
  QComboBox *colorFilter;  // Filter by compliance status color
  QLabel
    *nonCompliantSummary;  // Label to display summary of non-compliant sites
  WaterQalDataset *model;
};
