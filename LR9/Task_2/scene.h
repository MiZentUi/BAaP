#ifndef SCENE_H
#define SCENE_H

#include <QGraphicsScene>
#include <QGraphicsSceneMouseEvent>
#include "figure.h"
#include "figureType.h"

class Scene : public QGraphicsScene
{
    Q_OBJECT
    Q_PROPERTY(FigureType figureType READ getFigureType WRITE setFigureType NOTIFY figureTypeChanged FINAL)

public:
    explicit Scene(QObject *parent = nullptr);

    FigureType getFigureType() const;
    void setFigureType(const FigureType type);
    void setPenColor(QColor color);
    void setBrushColor(QColor color);
    void setPenWidth(qreal width);
    qreal getPenWidth();
    void deleteSelectedFigure();
    qreal getSelectedFigurePerimeter(bool &ok);
    qreal getSelectedFigureSquare(bool &ok);
    void removeAllItems();
    void un_select();

private:
    Figure *currentFigure;
    Figure *selectedFigure = nullptr;
    FigureType figureType;
    QColor currentPenColor;
    QColor currentBrushColor;
    qreal currentPenWidth = 1;
    QPointF pressPos;
    QPointF selectedStartPoint;
    QPointF selectedEndPoint;
    bool currentAdded = false;
    int currentSide = -1;
    enum
    {
        changing,
        moving,
        rotating,
        drawing
    }
    mode;
    qreal startRotation = 0;
    QPointF startRotateVector;
    qreal startAngel;
    qreal commonAngel = 0;
    qreal intermediateAngel = 0;

    void mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event);
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event);
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);
    Figure *figureAt(QPointF point);
    bool onRectBoard(QRectF rect, QPointF point, int &side);

signals:
    void figureTypeChanged();
};

#endif // SCENE_H
