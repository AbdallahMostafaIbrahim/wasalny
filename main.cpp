#include "mainwindow.h"

#include <QApplication>
#include <QDebug>

int main(int argc, char *argv[]) {
  Loader::init();
  QApplication a(argc, argv);
  MainWindow w;
  w.show();
  int result = a.exec();
  Loader::saveMap(*w.getMap());

  return result;
}
