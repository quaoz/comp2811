// COMP2811 Coursework 2: data model

#pragma once

#include <QAbstractTableModel>
<<<<<<< HEAD
=======
#include <QWidget>
#include <QApplication>
#include <QtCharts/QChartView>
#include <QtCharts/QLineSeries>
#include <QtCharts/QDateTimeAxis>
#include <QtCharts/QValueAxis>
#include <QDateTime>
#include <utility>  // for std::pair
#include <vector>
#include <QVector>
#include <QPointF>

//using namespace std;
#include <iostream>

>>>>>>> bd0649b (init)

#include "dataset.hpp"

class QuakeModel : public QAbstractTableModel {
 public:
  QuakeModel(QObject* parent = nullptr) : QAbstractTableModel(parent) {}
  void updateFromFile(const QString&);
  bool hasData() const { return dataset.size() > 0; }

  int rowCount(const QModelIndex& index) const { return dataset.size(); }
  int columnCount(const QModelIndex& index) const { return 17; }
  QVariant data(const QModelIndex&, int) const;
  QVariant headerData(int, Qt::Orientation, int) const;

<<<<<<< HEAD
 private:
  QuakeDataset dataset;
};
=======
  Sample getSample(int index) const { return dataset[index]; }
  //Determinand getDeterminand(int index) const { return dataset[index]; }

 private:
  QuakeDataset dataset;
};

// class PollutantGraph : public QWidget {
//   public:
//     PollutantGraph(QWidget *parent = nullptr) : QWidget(parent){}
//     // updateFromFile(const QString&);
//     bool hasData() const { return dataset.size() > 0; }

//     void data(const QModelIndex&, int);
//     //QVariant resultData(const QModelIndex&, int) const;

//     QVector<QPointF> getData() {
//       //cout << "data read";
//       return pollutantData;
//     }

//     //std::vector<std::pair<std::string, double>> pollutantData;
//   private:
//     QuakeDataset dataset;
//     //std::vector<std::pair<double, double>> pollutantData;
//     QVector<QPointF> pollutantData;
    
// };
>>>>>>> bd0649b (init)
