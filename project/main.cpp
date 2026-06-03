#include "controller/Controller.h"
#include "repo/GameRepo.h"
#include "ui/MainWin.h"
#include <QApplication>

int main(int argc, char *argv[]) {
  QApplication app(argc, argv);
  CSVRepo repo;
  Controller controller(repo);
  MainWindow window(&controller);
  window.show();
  return app.exec();
}
