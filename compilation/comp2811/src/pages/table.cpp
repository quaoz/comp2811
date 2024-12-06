#include "table.hpp"

#include <QFontDatabase>
#include <QTableView>
#include <QtWidgets>

WaterTable::WaterTable(QWidget* parent) : QWidget(parent) {
  table = new QTableView(this);
  table->setFont(QFontDatabase::systemFont(QFontDatabase::FixedFont));
  QVBoxLayout* layout = new QVBoxLayout(this);
  layout->addWidget(table);
  setLayout(layout);
}

void WaterTable::update(QuakeModel* model) {
  table->setModel(model);
  table->resizeColumnsToContents();
}
