#ifndef WIDGET_H
#define WIDGET_H

#include <QPainter>
#include <QThread>
#include <QWidget>
#include <QThread>
#include <QTimer>

class Widget : public QWidget
{
    Q_OBJECT
public:
    explicit Widget(QWidget *parent = nullptr);
    ~Widget();

    void startHanoi(int count);

private:
    const QStringList colors = {"red", "green", "blue", "magenta", "yellow", "cyan", "gray", "darkGreen"};
    QThread *secondThread;
    int count = 0;
    int *a = nullptr;
    int *b = nullptr;
    int *c = nullptr;

    void paintEvent(QPaintEvent *event);
    void loop();
    void hanoi(int count, int *a, int *b, int *c);
};

#endif // WIDGET_H
