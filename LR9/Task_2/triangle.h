#ifndef TRIANGLE_H
#define TRIANGLE_H

#include "figure.h"

#include "figureType.h"

class Triangle : public Figure
{
    Q_OBJECT

public:
    explicit Triangle(QPointF point, QObject *parent = nullptr);

    qreal getPerimeter();
    qreal getSquare();
    FigureType getFigureType();

private:
    QPolygonF polygon;

    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    QPainterPath shape() const;
};

#endif // TRIANGLE_H
