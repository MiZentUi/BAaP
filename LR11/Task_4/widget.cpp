#include "widget.h"

Widget::Widget(QWidget *parent) : QWidget{parent}, secondThread(new QThread())
{
    QObject::connect(secondThread, &QThread::started, [this] { loop(); });
}

Widget::~Widget()
{
    if (a != nullptr)
        delete[] a;
    if (b != nullptr)
        delete[] b;
    if (c != nullptr)
        delete[] c;
}

void Widget::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    painter.setPen(Qt::NoPen);
    qreal base_height = 50;
    qreal base_width = (qreal)width() / 5;

    qreal pin_height = (qreal)height() / 2;
    qreal pin_width = 25;

    painter.setBrush(Qt::black);

    painter.drawRoundedRect(
        QRectF(
            QPointF(base_width / 2, (qreal)height() * 0.75 + base_height / 2),
            QPointF(base_width * 1.5,
                    (qreal)height() * 0.75 - base_height / 2)),
        base_height / 2, base_height / 2);
    painter.drawRoundedRect(
        QRectF(QPointF(base_width - pin_width / 2, (qreal)height() / 4),
               QPointF(base_width + pin_width / 2,
                       (qreal)height() / 4 + pin_height)),
        base_height / 2, base_height / 2);

    painter.drawRoundedRect(
        QRectF(
            QPointF(base_width * 2, (qreal)height() * 0.75 + base_height / 2),
            QPointF(base_width * 3, (qreal)height() * 0.75 - base_height / 2)),
        base_height / 2, base_height / 2);
    painter.drawRoundedRect(
        QRectF(QPointF(base_width * 2.5 - pin_width / 2, (qreal)height() / 4),
               QPointF(base_width * 2.5 + pin_width / 2,
                       (qreal)height() / 4 + pin_height)),
        base_height / 2, base_height / 2);

    painter.drawRoundedRect(
        QRectF(
            QPointF(base_width * 3.5, (qreal)height() * 0.75 + base_height / 2),
            QPointF(base_width * 4.5,
                    (qreal)height() * 0.75 - base_height / 2)),
        base_height / 2, base_height / 2);
    painter.drawRoundedRect(
        QRectF(QPointF(base_width * 4 - pin_width / 2, (qreal)height() / 4),
               QPointF(base_width * 4 + pin_width / 2,
                       (qreal)height() / 4 + pin_height)),
        base_height / 2, base_height / 2);

    qreal ring_height = (pin_height - base_height) / count;
    if (ring_height > 40)
        ring_height = 40;
    qreal ring_max_width = base_width - pin_width;
    qreal ring_step = (base_width - pin_width) / count * 0.85;
    for (int i = 0; i < count; i++)
    {
        if (a[i])
        {
            painter.setBrush(QBrush(QColor(colors.at(a[i] % colors.size()))));
            painter.drawRoundedRect(
                QRectF(QPointF(base_width - (ring_max_width -
                                             ring_step * (count - a[i])) /
                                                2,
                               (qreal)height() * 0.75 - base_height / 2 -
                                   ring_height - ring_height * i),
                       QPointF(base_width + (ring_max_width -
                                             ring_step * (count - a[i])) /
                                                2,
                               (qreal)height() * 0.75 - base_height / 2 -
                                   ring_height * i)),
                ring_height / 2, ring_height / 2);
        }
    }
    for (int i = 0; i < count; i++)
    {
        if (b[i])
        {
            painter.setBrush(QBrush(QColor(colors.at(b[i] % colors.size()))));
            painter.drawRoundedRect(
                QRectF(QPointF(base_width * 2.5 - (ring_max_width -
                                                   ring_step * (count - b[i])) /
                                                      2,
                               (qreal)height() * 0.75 - base_height / 2 -
                                   ring_height - ring_height * i),
                       QPointF(base_width * 2.5 + (ring_max_width -
                                                   ring_step * (count - b[i])) /
                                                      2,
                               (qreal)height() * 0.75 - base_height / 2 -
                                   ring_height * i)),
                ring_height / 2, ring_height / 2);
        }
    }
    for (int i = 0; i < count; i++)
    {
        if (c[i])
        {
            painter.setBrush(QBrush(QColor(colors.at(c[i] % colors.size()))));
            painter.drawRoundedRect(
                QRectF(QPointF(base_width * 4 - (ring_max_width -
                                                 ring_step * (count - c[i])) /
                                                    2,
                               (qreal)height() * 0.75 - base_height / 2 -
                                   ring_height - ring_height * i),
                       QPointF(base_width * 4 + (ring_max_width -
                                                 ring_step * (count - c[i])) /
                                                    2,
                               (qreal)height() * 0.75 - base_height / 2 -
                                   ring_height * i)),
                ring_height / 2, ring_height / 2);
        }
    }
}

void Widget::startHanoi(int count)
{
    if (!secondThread->isRunning())
    {
        this->count = count;
        secondThread->start();
    }
}

void Widget::loop()
{
    if (a != nullptr)
    {
        delete[] a;
        a = nullptr;
    }
    if (b != nullptr)
    {
        delete[] b;
        b = nullptr;
    }
    if (c != nullptr)
    {
        delete[] c;
        c = nullptr;
    }
    a = new int[10]{};
    b = new int[10]{};
    c = new int[10]{};
    for (int i = 0; i < count; i++) a[i] = count - i;
    update();
    thread()->usleep(1000000 / this->count);
    hanoi(count, a, c, b);
    secondThread->terminate();
}

void Widget::hanoi(int count, int *A, int *B, int *C)
{
    if (count == 0)
        return;
    hanoi(count - 1, A, C, B);
    int t = this->count - 1;
    while (B[t] == 0 && t >= 0) t--;
    int f = this->count - 1;
    while (A[f] == 0) f--;
    B[t + 1] = A[f];
    A[f] = 0;
    update();
    secondThread->usleep(1000000 / this->count);
    hanoi(count - 1, C, B, A);
}