#ifndef EDGE_H
#define EDGE_H

#include <QGraphicsObject>

class Edge : public QGraphicsObject
{
Q_OBJECT
public:
    Edge(QPointF from, QPointF to, int weight);
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = nullptr) override;
    void focusInEvent(QFocusEvent *event) override;
    QRectF boundingRect() const override;
    QPainterPath shape() const override;
    void focusOut();
private:
    QPointF from;
    QPointF to;
    int weight;
    bool isFocused;
signals:
    void focused();
};

#endif // EDGE_H
