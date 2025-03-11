#include "figure.h"

#include <QCursor>
#include <QGraphicsSceneMouseEvent>
#include <qdebug.h>
#include <QGraphicsScene>

Figure::Figure(QPointF point, QObject *parent)
    : QObject{parent}
{
    this->setStartPoint(mapFromScene(point));
    this->setEndPoint(mapFromScene(point));
    connect(this, &Figure::pointChanged, this, &Figure::updateRect);
}

QRectF Figure::boundingRect() const
{
    return QRectF((getEndPoint().x() > getStartPoint().x() ? getStartPoint().x() : getEndPoint().x()) - 5,
                  (getEndPoint().y() > getStartPoint().y() ? getStartPoint().y() : getEndPoint().y()) - 5,
                  qAbs(getEndPoint().x() - getStartPoint().x()) + 10,
                  qAbs(getEndPoint().y() - getStartPoint().y()) + 10);
}

void Figure::updateRect()
{
    this->update((getEndPoint().x() > getStartPoint().x() ? getStartPoint().x() : getEndPoint().x()) - 5,
                 (getEndPoint().y() > getStartPoint().y() ? getStartPoint().y() : getEndPoint().y()) - 5,
                 qAbs(getEndPoint().x() - getStartPoint().x()) + 10,
                 qAbs(getEndPoint().y() - getStartPoint().y()) + 10);
}

void Figure::setStartPoint(const QPointF point)
{
    startPoint = mapFromScene(point);
    emit pointChanged();
}

void Figure::setEndPoint(const QPointF point)
{
    endPoint = mapFromScene(point);
    emit pointChanged();
}

void Figure::setPenColor(QColor color)
{
    penColor = color;
}

void Figure::setBrushColor(QColor color)
{
    brushColor = color;
}

void Figure::setPenWidth(qreal width)
{
    penWidth = width;
}

QPointF Figure::getStartPoint() const
{
    return startPoint;
}

QPointF Figure::getEndPoint() const
{
    return endPoint;
}

void Figure::select()
{
    selected = true;
}

void Figure::un_select()
{
    selected = false;
}

bool Figure::is_selected()
{
    return selected;
}

void Figure::painterInit(QPainter *painter)
{
    if (selected)
        drawSelectFrame(painter);
    painter->setPen(QPen(penColor, penWidth));
    if (brushColor.isValid() && brushColor != QColor(QStringLiteral("#1f1f1f")))
        painter->setBrush(brushColor);
}

void Figure::drawSelectFrame(QPainter *painter)
{
    painter->setPen(QPen(Qt::white, 1, Qt::DashDotLine));
    painter->drawRect(boundingRect());
    painter->drawPoint(boundingRect().center());
}
