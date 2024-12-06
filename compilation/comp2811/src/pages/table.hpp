#pragma once

#include <QTableView>
#include <QWidget>

#include "../data/model.hpp"

class QTableView;

class WaterTable : public QWidget {
  Q_OBJECT

 public:
  WaterTable(QWidget* parent = nullptr);
  void update(QuakeModel* model);

 private:
  QTableView* table;
};
