#ifndef EDGE_H
#define EDGE_H

#include <QGraphicsObject>

// Represents a Route between city to city in the scenee
class Edge : public QGraphicsObject {
  Q_OBJECT
public:
  // Takes two points, the names of the cities and distance, as parameters.
  Edge(QPointF from, QPointF to, QString fromCity, QString toCity, int weight);
  void paint(QPainter *painter, const QStyleOptionGraphicsItem *option,
             QWidget *widget = nullptr) override;
  void focusInEvent(QFocusEvent *event) override;
  QRectF boundingRect() const override;
  QPainterPath shape() const override;
  void focusOut();
  void focusIn();
  QString getFromCity();
  QString getToCity();

private:
  QPointF from;
  QPointF to;
  QString fromCity;
  QString toCity;
  int weight;
  bool isFocused;
signals:
  void focused();
};

#endif // EDGE_H
