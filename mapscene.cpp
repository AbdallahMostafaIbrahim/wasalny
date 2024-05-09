#include "mapscene.h"
#include <QGraphicsSceneMouseEvent>

MapScene::MapScene(QObject *parent) : QGraphicsScene(parent) {}

void MapScene::mousePressEvent(QGraphicsSceneMouseEvent *event) {
  QGraphicsScene::mousePressEvent(event);
  if (!itemAt(event->scenePos(), QTransform())) {
    emit unFocusEverything();
  }
}
