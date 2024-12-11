#include <QtWidgets>
#include <QTranslator>
#include <QLocale>
#include "window.hpp"

int main(int argc, char* argv[]) {
  QApplication app(argc, argv);

  // Create a translator instance
  QTranslator trn;
  if (trn.load(QLocale::system(), "quaketool", "_", ":/i18n")) {
    app.installTranslator(&trn);
  }

  QuakeWindow window;
  window.show();

  return app.exec();
}
