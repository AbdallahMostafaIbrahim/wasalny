#ifndef EDGE_H
#define EDGE_H

#include <QGraphicsObject>

class Edge : public QObject, public QGraphicsLineItem
{
Q_OBJECT
public:
    Edge(QPointF from, QPointF to, int weight);
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = nullptr) override;
private:
    QPointF from;
    QPointF to;
    int weight;
};

#endif // EDGE_H
