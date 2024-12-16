#include "card.hpp"

#include <QPushButton>
#include <QVBoxLayout>

#include "../window.hpp"

CardPopUp::CardPopUp(const QString& title, const QString& description,
                     const QString& secondaryText, QWidget* parent)
  : secondaryText(secondaryText), QDialog(parent) {
  setWindowTitle(title);

  QLabel* descriptionLabel = new QLabel(description);
  descriptionLabel->setStyleSheet("font-size: 14px; color: gray;");
  descriptionLabel->setAlignment(Qt::AlignCenter);
  descriptionLabel->setWordWrap(true);

  countLabel = new QLabel(QString(tr("Number of samples: 0")));
  countLabel->setAlignment(Qt::AlignCenter);

  secondaryLabel = new QLabel(secondaryText.arg(0));
  secondaryLabel->setAlignment(Qt::AlignCenter);

  QVBoxLayout* layout = new QVBoxLayout(this);
  layout->addWidget(descriptionLabel);
  layout->addWidget(countLabel);
  layout->addWidget(secondaryLabel);

  setLayout(layout);
}

void CardPopUp::updatePopUp(int sampleCount, int secondary) {
  countLabel->setText(QString(tr("Number of samples: %1")).arg(sampleCount));
  secondaryLabel->setText(secondaryText.arg(secondary));
}

OverviewCard::OverviewCard(const QString& title, const QString& description,
                           const QString& secondaryText, int tabID,
                           WaterQalWindow* windowInstance, QWidget* parent)
  : secondaryText(secondaryText),
    tabID(tabID),
    windowInstance(windowInstance),
    QFrame(parent) {
  // Set up the card's appearance
  setFrameStyle(QFrame::StyledPanel | QFrame::Raised);
  setLineWidth(2);
  setStyleSheet(
    "overviewCard {"
    "  border-radius: 8px;"
    "  border: 1px solid gray;"
    "  background-color: white;"
    "  padding: 10px;"
    "}"
    "overviewCard:hover {"
    "  background-color: #f0f8ff;"
    "}");

  popUp = new CardPopUp(title, description, secondaryText, this);

  // Layout for the card
  QVBoxLayout* layout = new QVBoxLayout(this);

  // Title label
  QLabel* titleLabel = new QLabel(title);
  titleLabel->setStyleSheet("font-weight: bold; font-size: 16px;");
  titleLabel->setAlignment(Qt::AlignCenter);

  // Description label
  QLabel* descriptionLabel = new QLabel(description);
  descriptionLabel->setStyleSheet("font-size: 14px; color: gray;");
  descriptionLabel->setAlignment(Qt::AlignCenter);
  descriptionLabel->setWordWrap(true);

  countLabel = new QLabel(QString(tr("Number of samples: 0")));
  countLabel->setAlignment(Qt::AlignCenter);

  secondaryLabel = new QLabel(secondaryText.arg(0));
  secondaryLabel->setAlignment(Qt::AlignCenter);

  QPushButton* actionButton = new QPushButton(tr("View more"), this);
  connect(actionButton, &QPushButton::clicked, this, &OverviewCard::switchTab);

  // Add widgets to the layout
  layout->addWidget(titleLabel);
  layout->addWidget(descriptionLabel);
  layout->addWidget(countLabel);
  layout->addWidget(secondaryLabel);
  layout->addWidget(actionButton);

  setLayout(layout);
}

void OverviewCard::updateCard(int sampleCount, int secondary) {
  countLabel->setText(QString(tr("Number of samples: %1")).arg(sampleCount));
  secondaryLabel->setText(secondaryText.arg(secondary));
  popUp->updatePopUp(sampleCount, secondary);
}

void OverviewCard::switchTab() { windowInstance->switchTab(tabID); }

void OverviewCard::showPopUp() { popUp->exec(); }
