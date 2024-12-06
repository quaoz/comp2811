#include <QtWidgets>

#include "window.hpp"

int main(int argc, char* argv[]) {
  QApplication app(argc, argv);

  QuakeWindow window;
  window.show();

  return app.exec();
}

//Coloured graph prototype:

// #include <QtWidgets/QApplication>
// #include <QtWidgets/QMainWindow>
// #include <QtCharts/QChartView>
// #include <QtCharts/QLineSeries>
// #include <QtCharts/QScatterSeries>
// #include <QtCharts/QValueAxis>

// //QT_CHARTS_USE_NAMESPACE

// int main(int argc, char *argv[])
// {
//   QApplication a(argc, argv);

  

//   QLineSeries *lineSeries = new QLineSeries();

//   QScatterSeries *scatterSeries = new QScatterSeries();
//   QScatterSeries *redSeries = new QScatterSeries();
//   scatterSeries->setMarkerSize(10.0);
//   redSeries->setMarkerSize(10.0);

//   lineSeries->append(0,6);
//   redSeries->append(0,6);
//   redSeries->setColor(Qt::red);

//   lineSeries->append(4,2);
//   scatterSeries->append(4,2);
//   scatterSeries->setColor(Qt::blue);

//   lineSeries->append(8,3);
//   scatterSeries->append(8,3);
//   scatterSeries->setColor(Qt::blue);

//   lineSeries->append(6,9);
//   scatterSeries->append(6,9);
//   scatterSeries->setColor(Qt::blue);

// QChart *chart = new QChart();

// chart->addSeries(lineSeries);
// chart->addSeries(scatterSeries);
// chart->addSeries(redSeries);

// QValueAxis *axisX = new QValueAxis();
// axisX->setTitleText("X-Axis");
// QValueAxis *axisY = new QValueAxis();
// axisY->setTitleText("Y-Axis");

// // Attach axes to the chart
// chart->addAxis(axisX, Qt::AlignBottom);
// chart->addAxis(axisY, Qt::AlignLeft);

// lineSeries->attachAxis(axisX);
// lineSeries->attachAxis(axisY);
// scatterSeries->attachAxis(axisX);
// scatterSeries->attachAxis(axisY);
// redSeries->attachAxis(axisX);
// redSeries->attachAxis(axisY);

// // Create the chart view
// QChartView *chartView = new QChartView(chart);
// chartView->setRenderHint(QPainter::Antialiasing);

// QMainWindow window;
// window.setCentralWidget(chartView);
// window.resize(400, 300);
// window.show();

// return a.exec();
// }
