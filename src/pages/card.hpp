#pragma once

#include <QFrame>
#include <QLabel>
#include <QPushButton>
#include <QWidget>

class QuakeWindow;

class OverviewCard : public QFrame {
  Q_OBJECT

 public:
  OverviewCard(const QString& title, int tabID, QuakeWindow* windowInstance,
               QWidget* parent = nullptr);
  void updateCard(int sampleCount);
  void switchTab();

 private:
  std::string cardTitle;
  int tabID;

  QuakeWindow* windowInstance;
  QLabel* countLabel;
};
