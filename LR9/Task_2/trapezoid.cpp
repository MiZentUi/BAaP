#include "trapezoid.h"

#include <cmath>

Trapezoid::Trapezoid(QPointF point, QObject *parent)
    : Figure{point, parent}
{}

void Trapezoid::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    painterInit(painter);
    polygon.clear();
    polygon << QPointF(getStartPoint().x() + (getEndPoint().x() < getStartPoint().x() ? -1 : 1) * qAbs(getEndPoint().x() - getStartPoint().x()) / 4, getStartPoint().y())
            << QPointF(getEndPoint().x() + (getEndPoint().x() < getStartPoint().x() ? 1 : -1) * qAbs(getEndPoint().x() - getStartPoint().x()) / 4, getStartPoint().y())
            << getEndPoint()
            << QPointF(getStartPoint().x(), getEndPoint().y());
    painter->drawPolygon(polygon);
}

QPainterPath Trapezoid::shape() const
{
    QPainterPath painter;
    painter.addPolygon(polygon);
    return painter;
}

qreal Trapezoid::getPerimeter()
{
    qreal perimeter = 0;
    for (int i = 0; i < polygon.size() - 1; i++)
        perimeter += std::sqrt(std::pow(polygon.at(i + 1).x() - polygon.at(i).x(), 2) + std::pow(polygon.at(i + 1).y() - polygon.at(i).y(), 2));
    if (polygon.size() > 1)
        perimeter += std::sqrt(std::pow(polygon.at(polygon.size() - 1).x() - polygon.at(0).x(), 2) + std::pow(polygon.at(polygon.size() - 1).y() - polygon.at(0).y(), 2));
    return perimeter;
}

qreal Trapezoid::getSquare()
{
    qreal sum = 0;
    int n = polygon.size();
    if (n > 1)
    {
        for (int i = 0; i < n - 1; i++)
        {
            sum += polygon.at(i).x() * polygon.at(i + 1).y();
            sum -= polygon.at(i + 1).x() * polygon.at(i).y();
        }
        sum += polygon.at(n - 1).x() * polygon.at(0).y();
        sum -= polygon.at(0).x() * polygon.at(n - 1).y();
    }
    return 0.5 * qAbs(sum);
}

FigureType Trapezoid::getFigureType()
{
    return trapezoid;
}
