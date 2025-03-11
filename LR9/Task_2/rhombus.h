#ifndef RHOMBUS_H
#define RHOMBUS_H

#include "figure.h"

#include "figureType.h"

class Rhombus : public Figure
{
public:
    explicit Rhombus(QPointF point, QObject *parent = nullptr);

    qreal getPerimeter();
    qreal getSquare();
    FigureType getFigureType();

private:
    QPolygonF polygon;

    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    QPainterPath shape() const;
};

#endif // RHOMBUS_H
