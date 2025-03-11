#ifndef ELLIPSE_H
#define ELLIPSE_H

#include <QGraphicsEllipseItem>
#include <QObject>
#include <QTimer>

class Ellipse : public QObject, public QGraphicsItem
{
    Q_OBJECT
public:
    explicit Ellipse(qreal x, qreal y, qreal width, qreal height, QObject *parent = nullptr);

    void start_fly(qreal speed);
    void stop_fly();
    void set_speed(qreal speed);
    void setVector(qreal x, qreal y);
    void draw(QPainter *painter);
    void moveOn(qreal d);
    void clean();

protected:
    qreal x;
    qreal y;
    qreal width;
    qreal height;
    qreal speed;

    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

private:
    QTimer *timer;
    qreal begin_y = 0;
    QPointF vector;
    bool cleaned = false;

private slots:
    void fly();
};

#endif // ELLIPSE_H
