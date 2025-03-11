#ifndef TRAPEZOID_H
#define TRAPEZOID_H

#include "figure.h"

#include "figureType.h"

class Trapezoid : public Figure
{
public:
    explicit Trapezoid(QPointF point, QObject *parent = nullptr);

    qreal getPerimeter();
    qreal getSquare();
    FigureType getFigureType();

private:
    QPolygonF polygon;

    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    QPainterPath shape() const;
};

#endif // TRAPEZOID_H
