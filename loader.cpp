#include "loader.h"
#include "map.h"
#include <QDebug>
#include <QDir>
#include <QMessageBox>
#include <QStandardPaths>
#include <QTextStream>

QFile *Loader::file = NULL;
Loader::Loader() {}

void Loader::init() {
  QString homeDir =
      QStandardPaths::writableLocation(QStandardPaths::HomeLocation);
  QString folderPath = homeDir + "/wasalny_data";

  QDir dir;

  if (!dir.exists(folderPath))
    dir.mkpath(folderPath);

  file = new QFile(folderPath + "/map.txt");
  if (!file->exists()) {
    file->open((QIODevice::ReadWrite | QIODevice::Text));
    file->close();
  }
}
void Loader::saveMap(Map m) {
  if (!file->open((QIODevice::ReadWrite | QIODevice::Text))) {
    qDebug() << file->errorString();
    QMessageBox::critical(0, "Error", "Couldn't load level");
  }
  QTextStream stream(file);
  file->resize(0);

  for (string city : m.getCities()) {

    MapCoordinates coordinates = m.getCityCoordinate(city);
    stream << QString::fromStdString(city) << " " << coordinates.x << " "
           << coordinates.y << "\n";

    for (pair<string, int> edge : m.getEdges(city)) {
      stream << QString::fromStdString(edge.first) << " " << edge.second
             << "\n";
    }
    stream << "#\n";
  }
  stream.flush();
  file->close();
}

Map Loader::loadMap() {
  if (!file->open(QIODevice::ReadOnly | QIODevice::Text)) {
    QMessageBox::critical(0, "Error", "Couldn't load level");
  }

  QTextStream in(file);
  Map map;
  QString line;
  QString currentCity;
  float x, y;

  while (!in.atEnd()) {
    line = in.readLine();
    if (line.isEmpty() || line.startsWith('#')) {
      // Skip empty lines and comments
      continue;
    }

    QStringList parts = line.split(' ', Qt::SkipEmptyParts);
    if (parts.size() == 3) {
      // It's a city description with coordinates
      currentCity = parts[0];
      x = parts[1].toFloat();
      y = parts[2].toFloat();
      map.addCity(currentCity.toStdString(), x, y);
    } else if (parts.size() == 2) {
      // It's an edge description
      QString toCity = parts[0];
      int distance = parts[1].toInt();
      map.addEdge(currentCity.toStdString(), toCity.toStdString(), distance);
    }
  }

  file->close();
  return map;
}
