#include "window1.h"

Window1::Window1(QWidget* parent) : QWidget(parent) {
    QVBoxLayout* layout = new QVBoxLayout(this);
    QLabel* label = new QLabel("This is Window 1", this);
    layout->addWidget(label);
}