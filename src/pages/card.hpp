#pragma once

#include <QFrame>
#include <QLabel>
#include <QPushButton>
#include <QWidget>

class WaterQalWindow;

class OverviewCard : public QFrame {
  Q_OBJECT

 public:
  OverviewCard(const QString& title, int tabID, WaterQalWindow* windowInstance,
               QWidget* parent = nullptr);
  void updateCard(int sampleCount);
  void switchTab();

 private:
  std::string cardTitle;
  int tabID;

  WaterQalWindow* windowInstance;
  QLabel* countLabel;
};
