#include "node.h"
#include <QBrush>
#include <QFocusEvent>
#include <QPainter>
#include <QPen>

// Node represents a city on the scene
Node::Node(qreal x, qreal y, qreal w, qreal h, QString c,
           QGraphicsItem *parent) {
  setFlags(ItemIsFocusable | ItemIsMovable | ItemSendsGeometryChanges);
  setPos(x - w / 2, y - h / 2);
  width = w;
  height = h;
  city = c;
  isFocused = false;
}

// Draws an elipse, and draws a thicker border if it is highlighted.
void Node::paint(QPainter *painter, const QStyleOptionGraphicsItem *option,
                 QWidget *widget) {
  painter->setBrush(QBrush(Qt::green));
  painter->setPen(QPen(Qt::black));
  if (isFocused) {
    painter->setPen(QPen(QBrush(Qt::black), 5));
  }
  painter->drawEllipse(0, 0, width, height);
  painter->drawText(0, -10, city);
}

QRectF Node::boundingRect() const { return QRectF(0, 0, width, height); }

void Node::focusOut() {
  isFocused = false;
  update();
}

QString Node::getCity() { return city; }

QVariant Node::itemChange(GraphicsItemChange change, const QVariant &value) {
  if (change == ItemPositionChange && scene()) {
    QPointF newPos = value.toPointF();
    emit positionChanged(newPos); // Signal to update position in Map class
  }

  return QGraphicsObject::itemChange(change, value);
}

void Node::focusInEvent(QFocusEvent *event) {
  isFocused = true;
  emit focused();
  update();
}
