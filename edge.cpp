#include "edge.h"
#include <QPainter>

Edge::Edge(QPointF f, QPointF t, QString fCity, QString tCity, int w)
    : from(f), to(t), fromCity(fCity), toCity(tCity), weight(w) {
  setFlags(ItemIsFocusable);
  isFocused = false;
}

// Draws Line between the two points and displays the distance over that line
void Edge::paint(QPainter *painter, const QStyleOptionGraphicsItem *option,
                 QWidget *widget) {
  painter->setPen(QPen(Qt::black));
  painter->drawText(QPointF((from.x() + to.x()) / 2, (from.y() + to.y()) / 2),
                    QString::number(weight));
  painter->setPen(QPen(Qt::blue));
  if (isFocused) {
    painter->setPen(QPen(QBrush(Qt::blue), 4));
  }
  painter->drawLine(from, to);
}

// Called to highlight edge and send a signal to the main window
void Edge::focusInEvent(QFocusEvent *event) {
  isFocused = true;
  emit focused();
  update();
}

QRectF Edge::boundingRect() const { return QRectF(from, to).normalized(); }

// Draws the shape that that will be used for the mouse to collide with
QPainterPath Edge::shape() const {
  QPainterPath path;

  QPen pen(Qt::blue, 1);
  if (isFocused) { // Draw a thicker line if it is highlighted
    pen.setWidth(4);
  }
  pen.setCapStyle(Qt::RoundCap);

  path.moveTo(from);
  path.lineTo(to);

  QPainterPathStroker stroker;
  stroker.setWidth(pen.widthF() + 2);
  stroker.setCapStyle(pen.capStyle());
  QPainterPath strokedPath = stroker.createStroke(path);
  path.addPath(strokedPath);

  return path;
}

// Removes the highlighted effect
void Edge::focusOut() {
  isFocused = false;
  update();
}

// Manually Applies highlighted effect. This is used for displaying the shortest path
void Edge::focusIn() {
  isFocused = true;
  update();
}

QString Edge::getFromCity() { return fromCity; }

QString Edge::getToCity() { return toCity; }
