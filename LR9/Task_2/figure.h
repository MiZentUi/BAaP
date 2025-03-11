#ifndef FIGURE_H
#define FIGURE_H

#include <QObject>
#include <QGraphicsItem>
#include <QPainter>

#include "figureType.h"

class Figure : public QObject, public QGraphicsItem
{
    Q_OBJECT
    Q_PROPERTY(QPointF startPoint READ getStartPoint WRITE setStartPoint NOTIFY pointChanged)
    Q_PROPERTY(QPointF endPoint READ getEndPoint WRITE setEndPoint NOTIFY pointChanged)
public:
    explicit Figure(QPointF pouint, QObject *parent = nullptr);

    QPointF getStartPoint() const;
    QPointF getEndPoint() const;
    void setStartPoint(const QPointF point);
    void setEndPoint(const QPointF point);
    void setPenColor(QColor color);
    void setBrushColor(QColor color);
    void setPenWidth(qreal width);
    void select();
    void un_select();
    bool is_selected();
    virtual qreal getPerimeter() = 0;
    virtual qreal getSquare() = 0;
    virtual FigureType getFigureType() = 0;
    QRectF boundingRect() const;

public slots:
    void updateRect();

private:
    QPointF startPoint;
    QPointF endPoint;

protected:
    QColor penColor;
    QColor brushColor = QColor(QStringLiteral("#eeeeee"));
    qreal penWidth = 1;
    bool selected = false;

    void painterInit(QPainter *painter);
    void drawSelectFrame(QPainter *painter);

signals:
    void pointChanged();
};

#endif // FIGURE_H
