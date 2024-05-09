#ifndef MAPSCENE_H
#define MAPSCENE_H

#include <QGraphicsScene>

class MapScene : public QGraphicsScene {
  Q_OBJECT
public:
  MapScene(QObject *parent = nullptr);
  void mousePressEvent(QGraphicsSceneMouseEvent *event) override;
signals:
  void unFocusEverything();
};

#endif // MAPSCENE_H
