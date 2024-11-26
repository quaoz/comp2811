#pragma once

#include <QWidget>

// Put forward references to widget classes here

class MyWindow: public QWidget
{
  public:
    MyWindow();

  private:
    void createWidgets();
    void arrangeWidgets();

    class QLineEdit;
    QLineEdit* nameField;
};