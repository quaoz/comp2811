#pragma once

#include <QDialog>
#include <QFrame>
#include <QLabel>
#include <QPushButton>
#include <QWidget>

class QDialog;
class WaterQalWindow;

class CardPopUp : public QDialog {
  Q_OBJECT

 public:
  CardPopUp(const QString& title, const QString& description,
            QWidget* parent = nullptr);
  void updatePopUp(int sampleCount, int secondary);

 private:
  QLabel* countLabel;
  QLabel* secondaryLabel;
};

class OverviewCard : public QFrame {
  Q_OBJECT

 public:
  OverviewCard(const QString& title, const QString& description, int tabID,
               WaterQalWindow* windowInstance, QWidget* parent = nullptr);
  void updateCard(int sampleCount, int secondary);
  void showPopUp();
  void switchTab();

 private:
  WaterQalWindow* windowInstance;
  int tabID;

  CardPopUp* popUp;
  QLabel* countLabel;
  QLabel* secondaryLabel;
};
