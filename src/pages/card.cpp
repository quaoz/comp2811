#include "card.hpp"

#include <QPushButton>
#include <QVBoxLayout>

#include "../window.hpp"

OverviewCard::OverviewCard(const QString& title, int tabID,
                           WaterQalWindow* windowInstance, QWidget* parent)
  : tabID(tabID), windowInstance(windowInstance), QFrame(parent) {
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

  // Layout for the card
  QVBoxLayout* layout = new QVBoxLayout(this);

  // Title label
  QLabel* titleLabel = new QLabel(title);
  titleLabel->setStyleSheet("font-weight: bold; font-size: 16px;");
  titleLabel->setAlignment(Qt::AlignCenter);

  countLabel = new QLabel(QString("Number of samples: 0"));
  countLabel->setAlignment(Qt::AlignCenter);

  QPushButton* actionButton = new QPushButton("View more", this);
  connect(actionButton, &QPushButton::clicked, this, &OverviewCard::switchTab);

  // Add widgets to the layout
  layout->addWidget(titleLabel);
  layout->addWidget(countLabel);
  layout->addWidget(actionButton);

  setLayout(layout);
}

void OverviewCard::updateCard(int sampleCount) {
  countLabel->setText(QString("Number of samples: %1").arg(sampleCount));
}

void OverviewCard::switchTab() { windowInstance->switchTab(tabID); }
