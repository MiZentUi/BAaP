#include "balloon.h"
#include <QDesktopWidget>
#include <QApplication>
#include <QGuiApplication>
#include <QScreen>
#include <QGraphicsScene>
#include <QGraphicsSceneMouseEvent>
#include <qdebug.h>
#include <random>


Balloon::Balloon(qreal x, qreal y, qreal width, qreal height, QObject *parent)
    : Ellipse{x, y, width, height, parent}
{
    this->triangle_width = width / 5;
    this->triangle_height = height / 10;
    burstPainter = new QPainter();
}

void Balloon::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    scene()->update(0, 0, 10000, 10000);
    if (burst)
    {
        foreach (Ellipse *e, parts)
        {
            // qDebug() << "draw" << "\n";
            e->update();
            e->moveOn(10);
        }
    }
    else
    {
        painter->setBrush(Qt::cyan);
        painter->setPen(Qt::cyan);
        drawBalloon(painter);
    }
}

QRectF Balloon::boundingRect() const
{
    return QRectF(x, y, width + 50, 2 * height + 50);
}

QPainterPath Balloon::shape() const
{
    QPainterPath p;
    p.addEllipse(x, y, width, height);
    return p;
}

void Balloon::setXc(qreal x)
{
    this->x = x;
}

qreal Balloon::getWidth()
{
    return width;
}

void Balloon::cleanBurst()
{
    foreach (Ellipse *e, parts)
    {
        e->clean();
        scene()->removeItem(e);
    }
    scene()->update(0, 0, 10000, 10000);
    parts.clear();
}

void Balloon::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    if (!bursted)
    {
        burstPos = event->pos();
        stop_fly();
        std::uniform_real_distribution<double> unif(-1, 1);
        std::default_random_engine re;
        re.seed(clock());
        cleanBurst();
        for (int i = 0; i < parts_count; i++)
        {
            Ellipse *ellipse = new Ellipse(burstPos.rx(), burstPos.ry(), width / parts_count * 2, height / parts_count * 2);
            qreal xe = unif(re), ye = unif(re);
            ellipse->setVector(xe, ye);
            scene()->addItem(ellipse);
            parts.push_back(ellipse);
        }
        burst = true;
        bursted = true;
    }
}

void Balloon::drawBalloon(QPainter *painter)
{
    draw(painter);
    QPolygonF polygon, polyline;
    polygon << QPointF(x + width / 2, y + height)
            << QPointF(x + (width - triangle_width) / 2, y + height + triangle_height)
            << QPointF(x + (width + triangle_width) / 2, y + height + triangle_height);
    painter->drawPolygon(polygon);
    painter->drawPoint(QPointF(3, 3));
    polyline << QPointF(x + width / 2, y + height)
             << QPointF(x + width / 2 + triangle_width / 4, y + height * 9 / 8)
             << QPointF(x + width / 2 - triangle_width / 4, y + height * 10 / 8)
             << QPointF(x + width / 2 + triangle_width / 4, y + height * 11 / 8)
             << QPointF(x + width / 2 - triangle_width / 4, y + height * 12 / 8)
             << QPointF(x + width / 2 + triangle_width / 4, y + height * 13 / 8);
    painter->drawPolyline(polyline);
}

void Balloon::reload()
{
    burst = false;
    cleanBurst();
    bursted = false;
}

void Balloon::setYc(qreal y)
{
    this->y = y;
}
