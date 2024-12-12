#include <QLocale>
#include <QTranslator>
#include <QtWidgets>

#include "window.hpp"

int main(int argc, char* argv[]) {
  QApplication app(argc, argv);

  // Create a translator instance
  QTranslator trn;

  // use QLocale("fr_FR") to force language
  if (trn.load(QLocale::system(), "waterqaltool", "_", ":/i18n")) {
    app.installTranslator(&trn);
  }

  WaterQalWindow window;
  window.show();

  return app.exec();
}
