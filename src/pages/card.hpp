#pragma once

#include <QDialog>
#include <QFrame>
#include <QLabel>
#include <QPushButton>
#include <QWidget>

class QDialog;
class WaterQalWindow;

/**
 * A pop-up dialog for displaying information about a card
 */
class CardPopUp : public QDialog {
  Q_OBJECT

 public:
  /**
   * Constructor
   *
   * @param title         The title of the pop-up
   * @param description   The description of the pop-up
   * @param secondaryText The secondary text of the pop-up
   * @param parent        The parent widget
   */
  CardPopUp(const QString& title, const QString& description,
            const QString& secondaryText, QWidget* parent = nullptr);

  /**
   * Updates the pop-up with the given sample count and secondary value
   *
   * @param sampleCount The sample count to display
   * @param secondary   The secondary value to display
   */
  void updatePopUp(int sampleCount, int secondary);

 private:
  QString secondaryText;
  QLabel* countLabel;
  QLabel* secondaryLabel;
};

/**
 * A card for displaying an overview of a dataset
 */
class OverviewCard : public QFrame {
  Q_OBJECT

 public:
  /**
   * Constructor
   *
   * @param title          The title of the card
   * @param description    The description of the card
   * @param secondaryText  The secondary text of the card
   * @param tabID          The ID of the tab the card is in
   * @param windowInstance The instance of the main window
   * @param parent         The parent widget
   */
  OverviewCard(const QString& title, const QString& description,
               const QString& secondaryText, int tabID,
               WaterQalWindow* windowInstance, QWidget* parent = nullptr);
  /**
   * Updates the card with the given sample count and secondary value
   *
   * @param sampleCount The sample count to display
   * @param secondary   The secondary value to display
   */
  void updateCard(int sampleCount, int secondary);
  /**
   * Shows the pop-up dialog
   */
  void showPopUp();
  /**
   * Switches to the tab associated with the card
   */
  void switchTab();

 private:
  WaterQalWindow* windowInstance;
  int tabID;

  QString secondaryText;
  CardPopUp* popUp;
  QLabel* countLabel;
  QLabel* secondaryLabel;
};
