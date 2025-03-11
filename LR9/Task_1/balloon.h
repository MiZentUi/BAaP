#ifndef BALLOON_H
#define BALLOON_H

#include "ellipse.h"
#include <QPainter>

class Balloon : public Ellipse
{
public:
    explicit Balloon(qreal x, qreal y, qreal width, qreal height, QObject *parent = nullptr);

    void setXc(qreal x);
    void setYc(qreal y);
    qreal getWidth();
    void reload();

private:
    qreal triangle_width;
    qreal triangle_height;
    qreal burstRadius = 0;
    QPainter *burstPainter;
    QPointF burstPos;
    QTimer *burstTimer;
    QVector<Ellipse *> parts;
    bool burst = false;
    bool bursted = false;
    int parts_count = 50;

    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    QRectF boundingRect() const;
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
    void drawBalloon(QPainter *painter);
    QPainterPath shape() const;
    void cleanBurst();
};

#endif // BALLOON_H
