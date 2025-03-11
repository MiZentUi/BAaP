#include "ellipse.h"

#include <QGuiApplication>
#include <QScreen>
#include <qdebug.h>
#include <qpainter.h>

Ellipse::Ellipse(qreal x, qreal y, qreal width, qreal height, QObject *parent)
    : QObject{parent}
{
    this->x = x;
    this->y = y;
    this->width = width;
    this->height = height;
    this->speed = 100;
    timer = new QTimer();
    connect(timer, &QTimer::timeout, this, &Ellipse::fly);
}

void Ellipse::set_speed(qreal speed)
{
    this->speed = speed;
}

void Ellipse::start_fly(qreal speed)
{
    this->speed = speed;
    timer->start(50);
}

void Ellipse::fly()
{
    y -= speed / 20;
    begin_y += speed / 20;
    if (y < -height * 1.6)
        y = (QGuiApplication::primaryScreen()->geometry()).height();
    if (begin_y > 200)
        begin_y = 0;
    if (begin_y < 100)
        x += speed / 20;
    else
        x -= speed / 20;
    update();
    timer->start(50);
}

void Ellipse::stop_fly()
{
    timer->stop();
}

void Ellipse::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    if (!cleaned)
        draw(painter);
    else
        painter->fillRect(boundingRect(), Qt::cyan);
}

void Ellipse::setVector(qreal x, qreal y)
{
    vector = QPointF(x, y);
}

void Ellipse::draw(QPainter *painter)
{
    painter->setPen(Qt::black);
    painter->setBrush(Qt::red);
    painter->drawEllipse(x, y, width, height);
}

void Ellipse::moveOn(qreal d)
{
    x += d * vector.rx();
    y += d * vector.ry();
}

QRectF Ellipse::boundingRect() const
{
    return QRectF(x, y, height + 50, width + 50);
}

void Ellipse::clean()
{
    cleaned = true;
    update();
}
