#include "edge.h"
#include <QPainter>

Edge::Edge(QPointF f, QPointF t, int w) : from(f), to(t), weight(w)
{
    setFlags(ItemIsFocusable);
    isFocused = false;
}

void Edge::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{

    painter->drawText(QPointF((from.x() + to.x()) / 2, (from.y() + to.y()) / 2), QString::number(weight));
    painter->setPen(QPen(Qt::blue));
    if(isFocused){
        painter->setPen(QPen(QBrush(Qt::blue), 4));
    }
    painter->drawLine(from, to);
}


void Edge::focusInEvent(QFocusEvent *event)
{
    isFocused = true;
    update();
}

void Edge::focusOutEvent(QFocusEvent *event)
{
    isFocused = false;
    update();
}

QRectF Edge::boundingRect() const
{
    return QRectF(from, to).normalized();
}

QPainterPath Edge::shape() const
{
    QPainterPath path;

    QPen pen(Qt::blue, 1);
    if (isFocused) {
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
