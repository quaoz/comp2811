#pragma once

#include <QtCharts/QChartView>
#include <QtCharts/QLineSeries>
#include <QtCharts/QScatterSeries>
#include <QValueAxis>
#include <QWidget>
#include <QLineEdit>
#include <QPushButton>
#include <QLabel>
#include <QVector>
#include <QPair>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include "../data/model.hpp"

class QTableView;

class PollutantPage : public QWidget {
  Q_OBJECT

 public:
  PollutantPage(QWidget* parent = nullptr);
  bool update(QuakeModel* model);
  void onSearchSubmit();
  void setModel(QuakeModel* quakeModel);
  void onDataPointClicked(const QPointF& point);

 private:
  QChartView* chartView;
  QLineSeries* series;
  QScatterSeries* scatterSeries;
  QLineEdit* searchInput;
  QPushButton* searchButton;
  QLabel* messageLabel;
  QString currentPollutant;
  QVector<QPair<double, QString>> dataPoints;
  QuakeModel *model;
  QPushButton* pollutant1Button; // Button for Pollutant 1
  QPushButton* pollutant2Button; // Button for Pollutant 2
};
