#pragma once

#include <QComboBox>
#include <QValueAxis>
#include <QWidget>
#include <QtCharts/QChartView>
#include <QtCharts/QDateTimeAxis>
#include <QtCharts/QLineSeries>
#include <QtCharts/QScatterSeries>
#include <set>

#include "../data/model.hpp"

class FluorinatedPage : public QWidget {
  Q_OBJECT

 public:
  FluorinatedPage(QWidget* parent = nullptr);
  void update(QuakeModel* model);

 private slots:
  void onComboBoxChanged();

 private:
  void filter();
  void onDataPointClicked(const QPointF& point);

  QChartView* chartView;
  QLineSeries* series;
  QScatterSeries* redSeries;
  QScatterSeries* yellowSeries;
  QScatterSeries* greenSeries;
  QDateTimeAxis* axisX;
  QValueAxis* axisY;
  QComboBox* locationComboBox;
  QComboBox* fluorinatedComboBox;
  QuakeModel* model;
  std::set<std::string> const fluorinatedCompounds = {
    "11Cl-PF3OUdS", "3:3 FTCA",     "4:2 FTSA",     "5:3 FTCA",
    "6:2 FTSA",     "7:3 FTCA",     "8:2 FTSA",     "9Cl-PF3ONS",
    "ADONA",        "B-[b]-fluora", "B-[k]-fluora", "EtFOSA",
    "EtFOSAA-B",    "EtFOSAA-L",    "FBSA",         "FLUORENE",
    "FOSA",         "Fluoranthene", "Fluoride - F", "Fluoroxypyr",
    "HFPO-DA",      "MeFOSAA-B",    "MeFOSAA-L",    "N-MeFOSA",
    "NFDHA",        "PFBA",         "PFBS",         "PFDS",
    "PFDoS",        "PFEESA",       "PFHpS",        "PFHxS-B",
    "PFHxS-L",      "PFHxSA",       "PFMOBA",       "PFMOPrA",
    "PFNS",         "PFODA",        "PFOS (B)",     "PFOS (L)",
    "PFOS",         "PFPeS",        "PFTrDA",       "PFUnDS",
    "PFdecncAcid",  "PFdodencAcid", "PFecHS",       "PFheptncAcid",
    "PFhexncAcid",  "PFnonncAcid",  "PFoctncAcid",  "PFpentncAcid",
    "PFtetdncAcid", "PFundencAcid", "TrCFMethan",   "pFoctanoate"};
};
