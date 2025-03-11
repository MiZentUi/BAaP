#include "polygon.h"
#include <cmath>

Polygon::Polygon(QPointF point, QObject *parent)
    : Figure{point, parent}
{
    currentPointsCount = pointsCount;
}

Polygon::Polygon(QPointF point, int currentPointsCount, QObject *parent)
    : Figure{point, parent}
{
    this->currentPointsCount = currentPointsCount;
}

void Polygon::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    painterInit(painter);
    radius = std::sqrt(std::pow(getEndPoint().x() - getStartPoint().x(), 2) + std::pow(getEndPoint().y() - getStartPoint().y(), 2));
    qreal step = 2 * M_PI / currentPointsCount;
    polygon.clear();
    for (int i = 0; i < currentPointsCount; i++)
        polygon << QPointF(getStartPoint().x() + std::cos(i * step - M_PI_2) * radius, getStartPoint().y() + std::sin(i * step - M_PI_2) * radius);
    painter->drawPolygon(polygon);
}

QRectF Polygon::boundingRect() const
{
    return QRectF(QPointF(getStartPoint().x() - radius, getStartPoint().y() - radius), QPointF(getStartPoint().x() + radius, getStartPoint().y() + radius));
}

QPainterPath Polygon::shape() const
{
    QPainterPath painter;
    painter.addPolygon(polygon);
    return painter;
}

int Polygon::pointsCount = 6;

void Polygon::setPointsCount(int count)
{
    pointsCount = count;
}

int Polygon::getPointsCount()
{
    return pointsCount;
}

qreal Polygon::getRadius()
{
    return radius;
}

qreal Polygon::getPerimeter()
{
    qreal perimeter = 0;
    for (int i = 0; i < polygon.size() - 1; i++)
        perimeter += std::sqrt(std::pow(polygon.at(i + 1).x() - polygon.at(i).x(), 2) + std::pow(polygon.at(i + 1).y() - polygon.at(i).y(), 2));
    if (polygon.size() > 1)
        perimeter += std::sqrt(std::pow(polygon.at(polygon.size() - 1).x() - polygon.at(0).x(), 2) + std::pow(polygon.at(polygon.size() - 1).y() - polygon.at(0).y(), 2));
    return perimeter;
}

qreal Polygon::getSquare()
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

FigureType Polygon::getFigureType()
{
    return FigureType::polygon;
}
