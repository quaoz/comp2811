#pragma once

#include <QTableView>
#include <QWidget>
#include <QtWidgets>
#include <QGridLayout>
#include <QPushButton>
#include <QLabel>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QtCharts/QChartView>
#include <QtCharts/QPieSeries>
#include <QFrame>

#include "../data/model.hpp"

class overviewCard : public QFrame {
 public:
  overviewCard(const QString& title, QWidget* parent = nullptr);
  void updateCard(QuakeModel* model, std::string cardType);
  void setPCBCounter(double counter);
  //double getPCBCounter(QuakeModel* model, double PCBCounter);

  private:
    double PCBCounter;
    QLabel* PCBCounterLabel;
    //QuakeModel model;


};

class QTableView;

class MainDashboardPage : public QWidget {
  Q_OBJECT

 public:
  MainDashboardPage(QWidget* parent = nullptr);
  void update(QuakeModel* model, overviewCard* PCBCard, overviewCard* litterCard);
  //void update(QuakeModel* model, overviewCard* PCBCard);


 private:
  //QChartView* chartView;
  //QPieSeries* series;
  //QuakeModel model;
  //overviewCard* PCBCard;
  QVBoxLayout* mainLayout;

};




// class overviewCard : public QFrame {
//     public:
//       //void getOverviewData(QuakeModel* model);
//       explicit overviewCard(const QString &title, QWidget *parent = nullptr) : QFrame(parent) {
//         // Set up the card's appearance
//         setFrameStyle(QFrame::StyledPanel | QFrame::Raised);
//         setLineWidth(2);
//         setStyleSheet("overviewCard {"
//                       "  border-radius: 8px;"
//                       "  border: 1px solid gray;"
//                       "  background-color: white;"
//                       "  padding: 10px;"
//                       "}"
//                       "overviewCard:hover {"
//                       "  background-color: #f0f8ff;"
//                       "}");

//         // Layout for the card
//         QVBoxLayout *layout = new QVBoxLayout(this);

//         // Title label
//         QLabel *titleLabel = new QLabel(title);
//         titleLabel->setStyleSheet("font-weight: bold; font-size: 16px;");
//         titleLabel->setAlignment(Qt::AlignCenter);

//         // Placeholder content
//         //double contentValue = getOverviewData(&model);
//         QLabel *contentLabel = new QLabel("content");
//         contentLabel->setAlignment(Qt::AlignCenter);

//         // Add sub-button
//         QPushButton *actionButton = new QPushButton("Action");
//         actionButton->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);

//         // Add widgets to the layout
//         layout->addWidget(titleLabel);
//         layout->addWidget(contentLabel);
//         layout->addWidget(actionButton);

//         setLayout(layout);
//     }
//   // Q_OBJECT

//   // public:
//   //   OverviewCard(const QString &title, QWidget *parent = nullptr) : QFrame(parent);



//         // explicit overviewCard(const QString &text, QWidget *parent = nullptr) : QWidget(parent) {
//         //     QVBoxLayout *cardLayout = new QVBoxLayout(this);

//         //     QLabel *cardLabel = new QLabel(text);
//         //     cardLabel->setAlignment(Qt::AlignCenter);

//         //     QPushButton *cardButton = new QPushButton("button");
//         //     cardButton->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);

//         //     cardLayout->addWidget(cardLabel);
//         //     cardLayout->addWidget(cardButton);

//         //     //setSizePolicy("overviewCard { border: 1px solid gray; border-radius: 5px; background-color: lightblue; padding: 5px; } overviewCard:hover { background-color: lightgreen; }");

//         //     setLayout(cardLayout);
//         // }
// };