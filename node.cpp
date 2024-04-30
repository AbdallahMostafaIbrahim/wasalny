#include "node.h"
#include <QPen>
#include <QBrush>
#include <QPainter>

Node::Node(qreal x, qreal y, qreal w, qreal h,QString c, QGraphicsItem *parent)
{
    setFlags(ItemIsMovable | ItemSendsGeometryChanges);
    setPos(x - w / 2, y - h /2);
    width = w;
    height = h;
    city = c;
}

void Node::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    painter->setBrush(QBrush(Qt::green));
    painter->setPen(QPen(Qt::black));
    painter->drawEllipse(0, 0, width, height);
    painter->drawText(0, -10, city);
}

QRectF Node::boundingRect() const
{
    return QRectF(0, 0, width, height);
}

QVariant Node::itemChange(GraphicsItemChange change, const QVariant &value)
{
    if (change == ItemPositionChange && scene()) {
        QPointF newPos = value.toPointF();
        emit positionChanged(newPos);  // Signal to update position in Map class
        update();
    }
    return QGraphicsObject::itemChange(change, value);
}
