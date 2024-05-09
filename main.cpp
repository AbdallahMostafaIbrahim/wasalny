#include "mainwindow.h"

#include <QApplication>
#include <QDebug>

int main(int argc, char *argv[]) {
  // Create Data File If it doesn't exist
  Loader::init();

  // Initialize Application
  QApplication a(argc, argv);
  MainWindow w;
  w.show();

  int result = a.exec();

  // Save Map to the data file when the program is over
  Loader::saveMap(*w.getMap());

  return result;
}
