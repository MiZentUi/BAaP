#include "square.h"

#include <cmath>

Square::Square(QPointF point, QObject *parent)
    : Figure{point, parent}
{}

void Square::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    painterInit(painter);
    polygon.clear();
    polygon << getStartPoint()
            << QPointF(getStartPoint().x() + (getEndPoint().x() < getStartPoint().x() ? -1 : 1) * std::min(qAbs(getEndPoint().y() - getStartPoint().y()), qAbs(getEndPoint().x() - getStartPoint().x())), getStartPoint().y())
            << QPointF(getStartPoint().x() + (getEndPoint().x() < getStartPoint().x() ? -1 : 1) * std::min(qAbs(getEndPoint().y() - getStartPoint().y()), qAbs(getEndPoint().x() - getStartPoint().x())),
                       getStartPoint().y() + (getEndPoint().y() < getStartPoint().y() ? -1 : 1) * std::min(qAbs(getEndPoint().y() - getStartPoint().y()), qAbs(getEndPoint().x() - getStartPoint().x())))
            << QPointF(getStartPoint().x(), getStartPoint().y() + (getEndPoint().y() < getStartPoint().y() ? -1 : 1) * std::min(qAbs(getEndPoint().y() - getStartPoint().y()), qAbs(getEndPoint().x() - getStartPoint().x())));
    painter->drawPolygon(polygon);
}

QPainterPath Square::shape() const
{
    QPainterPath painter;
    painter.addPolygon(polygon);
    return painter;
}

QRectF Square::boundingRect() const
{
    return QRectF(QPointF(getStartPoint().x() - (getEndPoint().x() < getStartPoint().x() ? -1 : 1) * 5, getStartPoint().y() - (getEndPoint().y() < getStartPoint().y() ? -1 : 1) * 5),
                  QPointF(getStartPoint().x() + (getEndPoint().x() < getStartPoint().x() ? -1 : 1) * (std::min(qAbs(getEndPoint().y() - getStartPoint().y()), qAbs(getEndPoint().x() - getStartPoint().x())) + 5),
                          getStartPoint().y() + (getEndPoint().y() < getStartPoint().y() ? -1 : 1) * (std::min(qAbs(getEndPoint().y() - getStartPoint().y()), qAbs(getEndPoint().x() - getStartPoint().x())) + 5)));
}

qreal Square::getPerimeter()
{
    qreal perimeter = 0;
    for (int i = 0; i < polygon.size() - 1; i++)
        perimeter += std::sqrt(std::pow(polygon.at(i + 1).x() - polygon.at(i).x(), 2) + std::pow(polygon.at(i + 1).y() - polygon.at(i).y(), 2));
    if (polygon.size() > 1)
        perimeter += std::sqrt(std::pow(polygon.at(polygon.size() - 1).x() - polygon.at(0).x(), 2) + std::pow(polygon.at(polygon.size() - 1).y() - polygon.at(0).y(), 2));
    return perimeter;
}

qreal Square::getSquare()
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

FigureType Square::getFigureType()
{
    return square;
}
