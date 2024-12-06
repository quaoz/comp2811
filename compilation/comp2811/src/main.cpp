// #include <QtWidgets>

// #include "window.hpp"

// int main(int argc, char* argv[]) {
//   QApplication app(argc, argv);

//   QuakeWindow window;
//   window.show();

//   return app.exec();
// }



#include <QtWidgets/QApplication>
#include <QtWidgets/QMainWindow>
#include <QtCharts/QChartView>
#include <QtCharts/QLineSeries>
#include <QtCharts/QScatterSeries>

//QT_CHARTS_USE_NAMESPACE

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QChart *chart = new QChart();

    //QLineSeries *series = new QLineSeries();

  QScatterSeries* redSeries = new QScatterSeries;
  redSeries->append(0, 6);
  redSeries->append(2, 4);
  redSeries->setColor(Qt::red);
  redSeries->setPen(QPen(Qt::blue));

  QScatterSeries* blueSeries = new QScatterSeries;
  blueSeries->append(3, 8);
  blueSeries->append(7, 4);
  blueSeries->append(10, 5);
  blueSeries->setColor(Qt::blue);

  chart->addSeries(redSeries);
  chart->addSeries(blueSeries);
  //redSeries.setPen(QPen(Qt::blue));

    // series->append(0, 6);
    // series->append(2, 4);
    // series->append(3, 8);
    // series->append(7, 4);
    // series->append(10, 5);
    // *series << QPointF(11, 1) << QPointF(13, 3) << QPointF(17, 6) << QPointF(18, 3) << QPointF(20, 2);

    // QChart *chart = new QChart();
    // chart->legend()->hide();
    // chart->addSeries(series);
    chart->createDefaultAxes();
    // chart->setTitle("Simple line chart example");

    QChartView *chartView = new QChartView(chart);
    chartView->setRenderHint(QPainter::Antialiasing);

    QMainWindow window;
    window.setCentralWidget(chartView);
    window.resize(400, 300);
    window.show();

    return a.exec();
}
