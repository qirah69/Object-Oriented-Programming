#include "mainWin.h"
#include <QApplication>

int main(int argc, char *argv[]) {
  qputenv("QT_QPA_PLATFORM", "wayland:darkmode=0");
  QApplication app(argc, argv);
  MainWindow w;
  w.show();
  return app.exec();
}
