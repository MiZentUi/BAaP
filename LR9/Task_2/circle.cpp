#include "circle.h"
#include "QDebug"
#include <cmath>

Circle::Circle(QPointF point, QObject *parent)
    : Figure{point, parent}
{}

void Circle::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    painterInit(painter);
    // a = qAbs(getEndPoint().x() - getStartPoint().x());
    // b = qAbs(getEndPoint().y() - getStartPoint().y());
    radius = std::sqrt(std::pow(getEndPoint().x() - getStartPoint().x(), 2) + std::pow(getEndPoint().y() - getStartPoint().y(), 2));
    // painter->drawEllipse(mapToScene(getStartPoint()), radius, radius);
    painter->drawEllipse(getStartPoint(), radius, radius);
}

QPainterPath Circle::shape() const
{
    QPainterPath painter;
    painter.addEllipse(getStartPoint(), radius, radius);
    return painter;
}

QRectF Circle::boundingRect() const
{
    return QRectF(QPointF(getStartPoint().x() - radius, getStartPoint().y() - radius), QPointF(getStartPoint().x() + radius, getStartPoint().y() + radius));
}

qreal Circle::getRadius()
{
    return radius;
}

qreal Circle::getPerimeter()
{
    return 2 * M_PI * radius;
}

qreal Circle::getSquare()
{
    return M_PI * radius * radius;
}

FigureType Circle::getFigureType()
{
    return circle;
}
