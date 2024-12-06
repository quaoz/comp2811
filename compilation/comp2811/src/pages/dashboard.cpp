#include "dashboard.hpp"

#include <QtWidgets>
#include <QGridLayout>
#include <QPushButton>
#include <QLabel>
#include <QVBoxLayout>
#include <QHBoxLayout>

overviewCard::overviewCard(const QString& title, QWidget* parent)
    : QFrame(parent), PCBCounter(5.0) {
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

  // Placeholder content
  //QLabel* contentLabel = new QLabel("content");
  //double PCBCounter = setPCBCounter(nullptr, 5.0);
  
  PCBCounterLabel = new QLabel(QString("Number of samples: %1").arg(PCBCounter));
  PCBCounterLabel->setAlignment(Qt::AlignCenter);

  // Add action button
  QPushButton* actionButton = new QPushButton("Action");
  actionButton->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);

  // Add widgets to the layout
  layout->addWidget(titleLabel);
  layout->addWidget(PCBCounterLabel);
  layout->addWidget(actionButton);

  setLayout(layout);
}

// double overviewCard::getPCBCounter(QuakeModel* model, double PCBCounter) {
//   // double counter = 1;
//   // double max = 0;
//   // //double PCBCounter = 0;
//   // for (int i = 0; i < (model->rowCount(QModelIndex())); i++) {
//   //   Sample SampleData = model->getSample(i);
//   //   counter = 5;

//   //   if (SampleData.getDeterminand().getLabel().find("PCBs")) {
//   //     //double result = SampleData.getResult();
//   //     counter = counter + 1;
//   //   }
//   // }
//   // PCBCounter = counter;
//   return PCBCounter;
//   //PCBCounterLabel->setText(QString("Counter: %1").arg(counter));
// }


void overviewCard::updateCard(QuakeModel* model, std::string cardType) {

  double tempPCBCounter = 0;
  for (int i = 0; i < model->rowCount(QModelIndex()); ++i) {
    Sample sampleData = model->getSample(i);
    if (sampleData.getDeterminand().getLabel().find(cardType) != std::string::npos) {
      tempPCBCounter++;
    }
  }

  PCBCounter = tempPCBCounter;
  PCBCounterLabel->setText(QString("Number of samples: %1").arg(PCBCounter));
  
}



// void overviewCard::setPCBCounter(double counter) {
//   PCBCounter = counter;
//   PCBCounterLabel->setText(QString("Counter: %1").arg(PCBCounter));
//   //double counter = 1;
//   //double max = 0;
//   //double PCBCounter = 0;
//   // for (int i = 0; i < (model->rowCount(QModelIndex())); i++) {
//   //   Sample SampleData = model->getSample(i);

//   //   if (SampleData.getDeterminand().getLabel().find("PCBs")) {
//   //     //double result = SampleData.getResult();
//   //     counter = counter + 1;
//   //   }
//   // }


// }


MainDashboardPage::MainDashboardPage(QWidget* parent) : QWidget(parent) {

  //Show range, location with highest level, locations over compliance levels
    
    // QGridLayout *overviewLayout = new QGridLayout;

    // overviewCard *POPsOverview = new overviewCard(QString("Button %1").arg(1));
    // overviewLayout->addWidget(POPsOverview, 0, 0);

    // overviewCard *EnviroOverview = new overviewCard(QString("Button %2").arg(2));
    // overviewLayout->addWidget(EnviroOverview, 0, 1);

    // overviewCard *FluorOverview = new overviewCard("F");
    // overviewLayout->addWidget(FluorOverview, 1, 0);

    // setLayout(overviewLayout);


    // for (int i = 0; i < 6; i++) {
    //     overviewCard *card = new overviewCard(QString("Button %1").arg(i+1));
    //     overviewLayout->addWidget(card, i / 2, i % 2);
    // }

    //setLayout(overviewLayout);
  //overviewCard PCBCard = new QVBoxLayout("Card 1 Title", this);

  mainLayout = new QVBoxLayout(this);

  // Example cards
  //PCBCard = new overviewCard("Card 1 Title", this);
  // //card1->setPCBCounter(nullptr, 10.0)

  // overviewCard* card2 = new overviewCard("Card 2 Title", this);

  // overviewCard* card3 = new overviewCard("Card 3 Title", this);

  // Add cards to the main layout
  //mainLayout->addWidget(PCBCard);
  // mainLayout->addWidget(card2);
  // mainLayout->addWidget(card3);

  //mainLayout->addWidget(PCBCard);

}

void MainDashboardPage::update(QuakeModel* model, overviewCard* PCBCard, overviewCard* litterCard) {
  //mainLayout = new QVBoxLayout(this);
  mainLayout->addWidget(litterCard);
  mainLayout->addWidget(PCBCard);
}



//void MainDashboardPage::update(QuakeModel* model, overviewCard* PCBCard) {
//   double currentPCBCounter = 0.0;
//   // for (int i = 0; i < model->rowCount(QModelIndex()); ++i) {
//   //   Sample SampleData = model->getSample(i);
//   //   if (SampleData.getDeterminand().getLabel().find("PCB") != std::string::npos) {
//   //     currentPCBCounter++;
//   //   }
//   // }

//   PCBCard->setPCBCounter(currentPCBCounter);

// }






// double overviewCard::getOverviewData(QuakeModel* model) {
//   Sample SampleData = model->getSample(i);

//   double counter = 0;
//   double max = 0;
//   double PCBCounter = 0;

//   for (int i = 0; i < (model->rowCount(QModelIndex())); i++) {
//     Sample SampleData = model->getSample(i);

//     if (SampleData.getDeterminand().getLabel().contains("PCB")) {
//       PCBCounter = PCBCounter + 1;
//     }

//   }

//   return PCBCounter;


//   table->setModel(model);
//   table->resizeColumnsToContents();
// }

// MainDashboardPage::MainDashboardPage(QWidget* parent) : QWidget(parent) {
    
//     QGridLayout *overviewLayout = new QGridLayout;

//     // OverviewCard *POPsOverview = new overviewCard("Card one");
//     // overviewLayout->addWidget(POPsOverview, 0, 0);

//     // OverviewCard *EnviroOverview = new overviewCard("Card two");
//     // overviewLayout->addWidget(EnviroOverview, 0, 1);

//     // OverviewCard *FluorOverview = new overviewCard("Card three");
//     // overviewLayout->addWidget(FluorOverview, 1, 0);




//     // for (int i = 0; i < 6; i++) {
//     //     overviewCard *card = new overviewCard(QString("Button %1").arg(i+1));
//     //     overviewLayout->addWidget(card, i / 2, i % 2);
//     // }

//     setLayout(overviewLayout);
// }

// // void setCardStyles(QFrame(parent)):
// //   setFrameStyle(QFrame::StyledPanel | QFrame::Raised);
// //         setLineWidth(2);
// //         setStyleSheet("Card {"
// //                       "  border-radius: 8px;"
// //                       "  border: 1px solid gray;"
// //                       "  background-color: white;"
// //                       "  padding: 10px;"
// //                       "}"
// //                       "Card:hover {"
// //                       "  background-color: #f0f8ff;"
// //                       "}");
// //     }
// //   ;




// OverviewCard* createOverviewCard(const QString &title, const QString &content, QWidget *parent = nullptr) {
//   OverviewCard *card = new OverviewCard(parent);

//   // Create the layout for the card
//   QVBoxLayout *layout = new QVBoxLayout(card);

//   // Add the title
//   QLabel *titleLabel = new QLabel(title);
//   titleLabel->setStyleSheet("font-weight: bold; font-size: 16px;");
//   titleLabel->setAlignment(Qt::AlignCenter);
//   layout->addWidget(titleLabel);

//   // Add the content
//   QLabel *contentLabel = new QLabel(content);
//   contentLabel->setAlignment(Qt::AlignCenter);
//   layout->addWidget(contentLabel);

//   // Add the button
//   QPushButton *actionButton = new QPushButton("Action");
//   actionButton->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);
//   layout->addWidget(actionButton);

//   // Set the layout to the card
//   card->setLayout(layout);

//   return card; // Return the created card
// }


// //   setFrameStyle(QFrame::StyledPanel | QFrame::Raised);
// //   setLineWidth(2);
// //   setStyleSheet("overviewCard {"
// //                 "  border-radius: 8px;"
// //                 "  border: 1px solid gray;"
// //                 "  background-color: white;"
// //                 "  padding: 10px;"
// //                 "}"
// //                 "overviewCard:hover {"
// //                 "  background-color: #f0f8ff;"
// //                 "}");

// //   // Layout for the card
// //   QVBoxLayout *layout = new QVBoxLayout(this);

// //   // Title label
// //   QLabel *titleLabel = new QLabel(title);
// //   titleLabel->setStyleSheet("font-weight: bold; font-size: 16px;");
// //   titleLabel->setAlignment(Qt::AlignCenter);

// //   // Placeholder content
// //   QLabel *contentLabel = new QLabel("This is card content.");
// //   contentLabel->setAlignment(Qt::AlignCenter);

// //   // Add sub-button
// //   QPushButton *actionButton = new QPushButton("Action");
// //   actionButton->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);

// //   // Add widgets to the layout
// //   layout->addWidget(titleLabel);
// //   layout->addWidget(contentLabel);
// //   layout->addWidget(actionButton);

// //   setLayout(layout);

// // }
// //overviewCard(const QString &title, QWidget *parent = nullptr) : QFrame(parent)

// // void overviewCard::getFluoroOverview(QuakeModel* model) {
// //   for (int i = 0; i < (model->rowCount(QModelIndex())); i++) {
// //     Sample SampleData = model->getSample(i);


// //   }
// // }

// // void MainDashboardPage::update(QuakeModel* model) {
  
// // }

// // void MainDashboardPage::update(QuakeModel* model) {
  
// // }