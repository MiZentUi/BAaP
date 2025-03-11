#include "star.h"
#include <cmath>

Star::Star(QPointF point, QObject *parent)
    : Figure{point, parent}
{
    currentPointsCount = pointsCount;
}

Star::Star(QPointF point, int currentPointsCount, QObject *parent)
    : Figure{point, parent}
{
    this->currentPointsCount = currentPointsCount;
}

void Star::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    painterInit(painter);
    radius = std::sqrt(std::pow(getEndPoint().x() - getStartPoint().x(), 2) + std::pow(getEndPoint().y() - getStartPoint().y(), 2));
    qreal step = M_PI / currentPointsCount;
    polygon.clear();
    for (int i = 0; i < currentPointsCount * 2; i++)
        polygon << QPointF(getStartPoint().x() + std::cos(i * step - M_PI_2) * radius * (i % 2 ? 0.5 : 1), getStartPoint().y() + std::sin(i * step - M_PI_2) * radius * (i % 2 ? 0.5 : 1));
    painter->drawPolygon(polygon);
}

QPainterPath Star::shape() const
{
    QPainterPath painter;
    painter.addPolygon(polygon);
    return painter;
}

int Star::pointsCount = 5;

void Star::setPointsCount(int count)
{
    pointsCount = count;
}

int Star::getPointsCount()
{
    return pointsCount;
}

QRectF Star::boundingRect() const
{
    return QRectF(QPointF(getStartPoint().x() - radius, getStartPoint().y() - radius), QPointF(getStartPoint().x() + radius, getStartPoint().y() + radius));
}

qreal Star::getRadius()
{
    return radius;
}

qreal Star::getPerimeter()
{
    qreal perimeter = 0;
    for (int i = 0; i < polygon.size() - 1; i++)
        perimeter += std::sqrt(std::pow(polygon.at(i + 1).x() - polygon.at(i).x(), 2) + std::pow(polygon.at(i + 1).y() - polygon.at(i).y(), 2));
    if (polygon.size() > 1)
        perimeter += std::sqrt(std::pow(polygon.at(polygon.size() - 1).x() - polygon.at(0).x(), 2) + std::pow(polygon.at(polygon.size() - 1).y() - polygon.at(0).y(), 2));
    return perimeter;
}

qreal Star::getSquare()
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

FigureType Star::getFigureType()
{
    return star;
}
