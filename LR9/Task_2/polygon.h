#ifndef POLYGON_H
#define POLYGON_H

#include "figure.h"

#include "figureType.h"

class Polygon : public Figure
{
public:
    explicit Polygon(QPointF point, QObject *parent = nullptr);
    explicit Polygon(QPointF point, int pointsCount, QObject *parent = nullptr);

    static void setPointsCount(int pointsCount);
    static int getPointsCount();
    qreal getRadius();
    qreal getPerimeter();
    qreal getSquare();
    FigureType getFigureType();

private:
    static int pointsCount;
    int currentPointsCount;
    QPolygonF polygon;
    qreal radius;

    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    QPainterPath shape() const;

    QRectF boundingRect() const;
};

#endif // POLYGON_H
