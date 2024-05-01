#include "edge.h"
#include <QPainter>

Edge::Edge(QPointF f, QPointF t, int w) : from(f), to(t), weight(w)
{

}

void Edge::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    painter->drawText(QPointF((from.x() + to.x()) / 2, (from.y() + to.y()) / 2), QString::number(weight));
    painter->setPen(QPen(Qt::blue));
    painter->drawLine(from, to);
}
