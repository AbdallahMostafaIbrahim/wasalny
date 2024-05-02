#ifndef NODE_H
#define NODE_H

#include <QGraphicsEllipseItem>
#include <QGraphicsSceneMouseEvent>

class Node : public QGraphicsObject
{
Q_OBJECT
private:
    int width;
    int height;
    QString city;
    bool isFocused;
public:
    Node(qreal x, qreal y, qreal w, qreal h, QString city, QGraphicsItem* parent = nullptr);
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = nullptr) override;
    QRectF boundingRect() const override;
    void focusOut();
    QString getCity();
protected:
    QVariant itemChange(GraphicsItemChange change, const QVariant &value) override;
    void focusInEvent(QFocusEvent *event) override;
signals:
    void positionChanged(const QPointF&);
    void focused();
};

#endif // NODE_H
