#include "dashboard.hpp"

#include <QGridLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QPushButton>
#include <QVBoxLayout>
#include <QtWidgets>

// TODO: card waffle, mean median + other stats, location filter

overviewCard::overviewCard(const QString& title, QTabWidget& tabWidget,
                           QWidget* parent)
  : QFrame(parent), PCBCounter(5.0), tabWidget(&tabWidget) {
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

  // Placeholder content
  // QLabel* contentLabel = new QLabel("content");
  // double PCBCounter = setPCBCounter(nullptr, 5.0);

  PCBCounterLabel =
    new QLabel(QString("Number of samples: %1").arg(PCBCounter));
  PCBCounterLabel->setAlignment(Qt::AlignCenter);

  // Add action button
  // QPushButton* actionButton = new QPushButton("Action");
  // std::string cardTitle = title.toStdString();
  QPushButton* actionButton = new QPushButton("View more", this);
  connect(actionButton, &QPushButton::clicked, this, &overviewCard::openWindow);
  // actionButton->setSizePolicy(QSizePolicy::Expanding,
  // QSizePolicy::Preferred);

  // Add widgets to the layout
  layout->addWidget(titleLabel);
  layout->addWidget(PCBCounterLabel);
  layout->addWidget(actionButton);

  setLayout(layout);
}

void overviewCard::openWindow() {
  tabWidget->setCurrentIndex(1);
  // if (cardTitle == "PCBs compounds overview"){
  //   tabWidget->setCurrentIndex(4);
  // } else if (cardTitle == "Environmental litter compound") {
  //   tabWidget->setCurrentIndex(1);
  // } else if (cardTitle == "Fluorinated compounds overview"){
  //   tabWidget->setCurrentIndex(0);
  // }
}

// TODO: inefficient
void overviewCard::updateCard(QuakeModel* model, std::string cardType) {
  double tempPCBCounter = 0;
  for (int i = 0; i < model->rowCount(QModelIndex()); ++i) {
    Sample sampleData = model->getSample(i);
    if (sampleData.getDeterminand().getLabel().find(cardType) !=
        std::string::npos) {
      tempPCBCounter++;
    }
  }

  PCBCounter = tempPCBCounter;
  PCBCounterLabel->setText(QString("Number of samples: %1").arg(PCBCounter));
}

MainDashboardPage::MainDashboardPage(QWidget* parent) : QWidget(parent) {
  mainLayout = new QVBoxLayout(this);
}

void MainDashboardPage::update(QuakeModel* model, overviewCard* PCBCard,
                               overviewCard* litterCard,
                               overviewCard* fluoroCard) {
  // mainLayout = new QVBoxLayout(this);
  mainLayout->addWidget(litterCard);
  mainLayout->addWidget(PCBCard);
  mainLayout->addWidget(fluoroCard);
}
