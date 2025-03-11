#ifndef SQUARE_H
#define SQUARE_H

#include "figure.h"

#include "figureType.h"

class Square : public Figure
{
public:
    explicit Square(QPointF point, QObject *parent = nullptr);

    qreal getPerimeter();
    qreal getSquare();
    FigureType getFigureType();

private:
    QPolygonF polygon;

    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    QPainterPath shape() const;
    QRectF boundingRect() const;
};

#endif // SQUARE_H
