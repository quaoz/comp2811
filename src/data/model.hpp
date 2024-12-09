#pragma once

#include <QAbstractTableModel>
#include <set>

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

  Sample getSample(int index) const { return dataset[index]; }
  std::set<std::string> getLocations() const { return dataset.getLocations(); }
  std::set<std::string> getPollutants() const {
    return dataset.getPollutants();
  }

 private:
  QuakeDataset dataset;
};
