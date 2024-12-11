#include "dashboard.hpp"

#include <QtWidgets>
#include <QGridLayout>
#include <QPushButton>
#include <QLabel>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QDesktopServices>
#include <QUrl>
#include <QProcess>


overviewCard::overviewCard(const QString& title,const QString& description, QTabWidget& tabWidget, QWidget* parent)
    : QFrame(parent), PCBCounter(5.0), meanResult(5.0), tabWidget(&tabWidget) {
  // Set up the card's appearance
  setFrameStyle(QFrame::StyledPanel | QFrame::Raised);
  setLineWidth(2);
  setStyleSheet("overviewCard {"
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

  // Description label
  QLabel* descriptionLabel = new QLabel(description);
  descriptionLabel->setStyleSheet("font-size: 14px; color: gray;");
  descriptionLabel->setAlignment(Qt::AlignCenter);
  descriptionLabel->setWordWrap(true);

  // Placeholder content
  //QLabel* contentLabel = new QLabel("content");
  //double PCBCounter = setPCBCounter(nullptr, 5.0);
  MeanLabel = new QLabel(QString("Mean of samples: %1").arg(meanResult));
  MeanLabel->setAlignment(Qt::AlignCenter);

  PCBCounterLabel = new QLabel(QString("Number of samples: %1").arg(PCBCounter));
  PCBCounterLabel->setAlignment(Qt::AlignCenter);

  QLabel* footerLabel = new QLabel(this);
footerLabel->setText("<a href=\"https://doc.qt.io/qt-6/qtmodules.html\">Data Source</a>");
footerLabel->setOpenExternalLinks(false); // Disable automatic handling of links

connect(footerLabel, &QLabel::linkActivated, [](const QString &link) {
    QString chromePath;

#ifdef Q_OS_WINDOWS
    chromePath = "C:/Program Files/Google/Chrome/Application/chrome.exe"; // Default path for Chrome on Windows
#elif defined(Q_OS_MACOS)
    chromePath = "/Applications/Google Chrome.app/Contents/MacOS/Google Chrome";
#elif defined(Q_OS_LINUX)
    chromePath = "google-chrome"; // Assuming Chrome is in the PATH
#endif

    // Launch Google Chrome with the URL
    if (!chromePath.isEmpty()) {
        QProcess::startDetached(chromePath, QStringList() << link);
    } else {
        QDesktopServices::openUrl(QUrl(link)); // Fallback to the default browser
    }
});
  // Add action button
  //QPushButton* actionButton = new QPushButton("Action");
  //std::string cardTitle = title.toStdString();

  QPushButton* actionButton = new QPushButton("View more", this);
  connect(actionButton, &QPushButton::clicked, this, &overviewCard::openWindow);
  //actionButton->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);

  // Add widgets to the layout
  layout->addWidget(titleLabel);
  layout->addWidget(descriptionLabel);
  layout->addWidget(MeanLabel);
  layout->addWidget(PCBCounterLabel);
  layout->addWidget(actionButton);
  layout->addWidget(footerLabel);
  
  setLayout(layout);
}

void overviewCard::openWindow(){
  tabWidget->setCurrentIndex(1);
  // if (cardTitle == "PCBs compounds overview"){
  //   tabWidget->setCurrentIndex(4);
  // } else if (cardTitle == "Environmental litter compound") {
  //   tabWidget->setCurrentIndex(1);
  // } else if (cardTitle == "Fluorinated compounds overview"){
  //   tabWidget->setCurrentIndex(0);
  // }
}


void overviewCard::updateCard(QuakeModel* model, std::string cardType) {
  float totalResult = 0;
  float tempPCBCounter = 0;
  for (int i = 0; i < model->rowCount(QModelIndex()); ++i) {
    Sample sampleData = model->getSample(i);
    if (sampleData.getDeterminand().getLabel().find(cardType) != std::string::npos) {
      totalResult = totalResult + sampleData.getResult();
      tempPCBCounter++;
    }
  }

  // float totalResult = 0;
  // for (int i = 0; i < model->rowCount(QModelIndex()); ++i) {
  //   Sample sampleData = model->getSample(i);
  //   if (sampleData.getResult().find(cardType) != std::string::npos) {
  //     totalResult++;
  //   }
  // }

  float meanResult = totalResult/tempPCBCounter;

  MeanLabel->setText(QString("Mean of samples: %1").arg(meanResult));

  PCBCounter = tempPCBCounter;
  PCBCounterLabel->setText(QString("Number of samples: %1").arg(PCBCounter));
  
}



MainDashboardPage::MainDashboardPage(QWidget* parent) : QWidget(parent) {

  mainLayout = new QVBoxLayout(this);

}

void MainDashboardPage::update(QuakeModel* model, overviewCard* PCBCard, overviewCard* litterCard, overviewCard* fluoroCard) {
  //mainLayout = new QVBoxLayout(this);
  mainLayout->addWidget(litterCard);
  mainLayout->addWidget(PCBCard);
  mainLayout->addWidget(fluoroCard);
}