#include "scene.h"

#include "circle.h"
#include "polygon.h"
#include "rectangle.h"
#include "rhombus.h"
#include "square.h"
#include "star.h"
#include "trapezoid.h"
#include "triangle.h"

#include <QGraphicsView>
#include <QInputDialog>
#include <qdebug.h>
#include <cmath>

Scene::Scene(QObject *parent)
    : QGraphicsScene{parent}
{}

FigureType Scene::getFigureType() const
{
    return figureType;
}

void Scene::setFigureType(const FigureType type)
{
    figureType = type;
}

void Scene::setPenColor(QColor color)
{
    currentPenColor = color;
}

void Scene::setBrushColor(QColor color)
{
    currentBrushColor = color;
}

void Scene::setPenWidth(qreal width)
{
    currentPenWidth = width;
}

qreal Scene::getPenWidth()
{
    return currentPenWidth;
}

void Scene::mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event)
{
    Figure *tempFigure = figureAt(event->scenePos());
    if (selectedFigure != nullptr && selectedFigure != tempFigure)
    {
        pressPos = event->scenePos();
        selectedFigure->un_select();
        selectedFigure->update();
    }
    selectedFigure = tempFigure;
    if (selectedFigure)
    {
        pressPos = event->scenePos();
        selectedStartPoint = selectedFigure->getStartPoint();
        selectedEndPoint = selectedFigure->getEndPoint();
        selectedFigure->select();
        selectedFigure->update();
    }
    this->update(QRectF(0, 0, this->width(), this->height()));
}

void Scene::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    if (selectedFigure != nullptr && selectedFigure->is_selected())
    {
        pressPos = event->scenePos();
        selectedStartPoint = selectedFigure->getStartPoint();
        selectedEndPoint = selectedFigure->getEndPoint();
        if (onRectBoard(selectedFigure->boundingRect(), event->scenePos(), currentSide))
            mode = changing;
        else if (selectedFigure->boundingRect().contains(event->scenePos()))
            mode = moving;
        else
        {
            QPointF center = selectedFigure->boundingRect().center();
            startRotateVector = QPointF(pressPos.x() - center.x(), pressPos.y() - center.y());
            startRotation = selectedFigure->rotation();
            startAngel = std::atan2(startRotateVector.y(), startRotateVector.x()) * 180 / M_PI;
            commonAngel = 0;
            intermediateAngel = 0;
            mode = rotating;
        }
        selectedFigure->update();
    }
    switch (figureType)
    {
    case triangle:
        currentFigure = new Triangle(event->scenePos());
        break;
    case circle:
        currentFigure = new Circle(event->scenePos());
        break;
    case rhombus:
        currentFigure = new Rhombus(event->scenePos());
        break;
    case square:
        currentFigure = new Square(event->scenePos());
        break;
    case rectangle:
        currentFigure = new Rectangle(event->scenePos());
        break;
    case star:
        currentFigure = new Star(event->scenePos());
        break;
    case polygon:
        currentFigure = new Polygon(event->scenePos());
        break;
    case trapezoid:
        currentFigure = new Trapezoid(event->scenePos());
        break;
    default:
        currentFigure = new Triangle(event->scenePos());
        break;
    }
    currentFigure->setPos(event->pos());
    currentFigure->setPenColor(currentPenColor);
    currentFigure->setBrushColor(currentBrushColor);
    currentFigure->setPenWidth(currentPenWidth);
    currentAdded = false;
    this->update(QRectF(0, 0, this->width(), this->height()));
}

void Scene::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    if (selectedFigure != nullptr && selectedFigure->is_selected())
    {
        if (mode == changing)
        {
            qreal dx = event->scenePos().x() - pressPos.x();
            qreal dy = event->scenePos().y() - pressPos.y();
            FigureType selectedFigureType = selectedFigure->getFigureType();
            if (selectedFigureType == circle || selectedFigureType == star || selectedFigureType == polygon)
            {
                qreal radius = std::sqrt(std::pow(selectedEndPoint.x() - selectedStartPoint.x(), 2) + std::pow(selectedEndPoint.y() - selectedStartPoint.y(), 2));
                switch (currentSide)
                {
                case 0:
                    selectedEndPoint.y() > selectedStartPoint.y() ? selectedFigure->setEndPoint(QPointF(selectedStartPoint.x() + (selectedEndPoint.x() - selectedStartPoint.x()) * (1 - dy / radius), selectedStartPoint.y() + (selectedEndPoint.y() - selectedStartPoint.y()) * (1 - dy / radius)))
                                                                  : selectedFigure->setEndPoint(QPointF(selectedStartPoint.x() + (selectedEndPoint.x() - selectedStartPoint.x()) * (1 + dy / radius), selectedStartPoint.y() + (selectedEndPoint.y() - selectedStartPoint.y()) * (1 + dy / radius)));
                    break;
                case 1:
                    selectedEndPoint.y() > selectedStartPoint.y() ? selectedFigure->setEndPoint(QPointF(selectedStartPoint.x() + (selectedEndPoint.x() - selectedStartPoint.x()) * (1 + dx / radius), selectedStartPoint.y() + (selectedEndPoint.y() - selectedStartPoint.y()) * (1 + dx / radius)))
                                                                  : selectedFigure->setEndPoint(QPointF(selectedStartPoint.x() + (selectedEndPoint.x() - selectedStartPoint.x()) * (1 - dx / radius), selectedStartPoint.y() + (selectedEndPoint.y() - selectedStartPoint.y()) * (1 - dx / radius)));
                    break;
                case 2:
                    selectedEndPoint.y() > selectedStartPoint.y() ? selectedFigure->setEndPoint(QPointF(selectedStartPoint.x() + (selectedEndPoint.x() - selectedStartPoint.x()) * (1 + dy / radius), selectedStartPoint.y() + (selectedEndPoint.y() - selectedStartPoint.y()) * (1 + dy / radius)))
                                                                  : selectedFigure->setEndPoint(QPointF(selectedStartPoint.x() + (selectedEndPoint.x() - selectedStartPoint.x()) * (1 - dy / radius), selectedStartPoint.y() + (selectedEndPoint.y() - selectedStartPoint.y()) * (1 - dy / radius)));
                    break;
                case 3:
                    selectedEndPoint.y() > selectedStartPoint.y() ? selectedFigure->setEndPoint(QPointF(selectedStartPoint.x() + (selectedEndPoint.x() - selectedStartPoint.x()) * (1 - dx / radius), selectedStartPoint.y() + (selectedEndPoint.y() - selectedStartPoint.y()) * (1 - dx / radius)))
                                                                  : selectedFigure->setEndPoint(QPointF(selectedStartPoint.x() + (selectedEndPoint.x() - selectedStartPoint.x()) * (1 + dx / radius), selectedStartPoint.y() + (selectedEndPoint.y() - selectedStartPoint.y()) * (1 + dx / radius)));
                    break;
                default:
                    break;
                }
            }
            else
            {
                switch (currentSide)
                {
                case 0:
                    selectedEndPoint.y() > selectedStartPoint.y() ? selectedFigure->setStartPoint(QPointF(selectedStartPoint.x(), selectedStartPoint.y() + dy))
                                                                  : selectedFigure->setEndPoint(QPointF(selectedEndPoint.x(), selectedEndPoint.y() + dy));
                    break;
                case 1:
                    selectedEndPoint.x() > selectedStartPoint.x() ? selectedFigure->setEndPoint(QPointF(selectedEndPoint.x() + dx, selectedEndPoint.y()))
                                                                  : selectedFigure->setStartPoint(QPointF(selectedStartPoint.x() + dx, selectedStartPoint.y()));
                    break;
                case 2:
                    selectedEndPoint.y() > selectedStartPoint.y() ? selectedFigure->setEndPoint(QPointF(selectedEndPoint.x(), selectedEndPoint.y() + dy))
                                                                  : selectedFigure->setStartPoint(QPointF(selectedStartPoint.x(), selectedStartPoint.y() + dy));
                    break;
                case 3:
                    selectedEndPoint.x() > selectedStartPoint.x() ? selectedFigure->setStartPoint(QPointF(selectedStartPoint.x() + dx, selectedStartPoint.y()))
                                                                  : selectedFigure->setEndPoint(QPointF(selectedEndPoint.x() + dx, selectedEndPoint.y()));
                    break;
                default:
                    break;
                }
            }
        }
        else if (mode == moving)
        {
            qreal dx = event->scenePos().x() - pressPos.x();
            qreal dy = event->scenePos().y() - pressPos.y();
            selectedFigure->setStartPoint(QPointF(selectedStartPoint.x() + dx, selectedStartPoint.y() + dy));
            selectedFigure->setEndPoint(QPointF(selectedEndPoint.x() + dx, selectedEndPoint.y() + dy));
        }
        else if (mode == rotating)
        {
            QPointF center = selectedFigure->boundingRect().center();
            QPointF currentRotateVector = QPointF(event->scenePos().x() - center.x(), event->scenePos().y() - center.y());
            qreal currentAngle = std::atan2(currentRotateVector.y(), currentRotateVector.x()) * 180 / M_PI;
            qreal angleDelta = currentAngle - startAngel;
            if (angleDelta > 180)
                angleDelta -= 360;
            else if (angleDelta < -180)
                angleDelta += 360;
            selectedFigure->setTransformOriginPoint(center);
            selectedFigure->setRotation(startRotation + angleDelta);

            // qreal angel = (((startRotateVector.x() - center.x()) * (currentRotateVector.y() - center.y()) - (currentRotateVector.x() - center.x()) * (startRotateVector.y() - center.y())) > 0 ? 1 : 1) * 180 / M_PI * std::acos((startRotateVector.x() * currentRotateVector.x() + startRotateVector.y() * currentRotateVector.y()) / (std::sqrt(std::pow(startRotateVector.x(), 2) + std::pow(startRotateVector.y(), 2)) * std::sqrt(std::pow(currentRotateVector.x(), 2) + std::pow(currentRotateVector.y(), 2))));
            // // qreal angel = std::atan2(currentRotateVector.y() - center.y(), currentRotateVector.x() - center.x()) - std::atan2(startRotateVector.y() - center.y(), startRotateVector.x() - center.x());
            // intermediateAngel += angel;
            // // qDebug() << (((startRotateVector.x() - center.x()) * (currentRotateVector.y() - center.y()) - (currentRotateVector.x() - center.x()) * (startRotateVector.y() - center.y())) > 0 ? -1 : 1);
            // if (qAbs(intermediateAngel) > 100)
            // {
            //     startRotateVector = currentRotateVector;
            //     commonAngel += angel;
            //     intermediateAngel = 0;
            // }
            // else
            // {
            //     selectedFigure->setTransformOriginPoint(center);
            //     selectedFigure->setRotation(startRotation + commonAngel + angel);
            // }
            // qDebug() << startRotateVector << " " << currentRotateVector;
            // qDebug() << std::acos((startRotateVector.x() * currentRotateVector.x() + startRotateVector.y() * currentRotateVector.y()) / (std::sqrt(std::pow(startRotateVector.x(), 2) + std::pow(startRotateVector.y(), 2)) * std::sqrt(std::pow(currentRotateVector.x(), 2) + std::pow(currentRotateVector.y(), 2))));
        }
        selectedFigure->update();
    }
    else
    {
        if (!currentAdded)
        {
            this->addItem(currentFigure);
            currentAdded = true;
        }
        currentFigure->setEndPoint(event->scenePos());
    }
    this->update(QRectF(0, 0, this->width(), this->height()));
}

void Scene::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    if (selectedFigure != nullptr && selectedFigure->is_selected() && mode == rotating && qAbs(pressPos.x() - event->scenePos().x()) < 10 && qAbs(pressPos.y() - event->scenePos().y()) < 10)
    {
        selectedFigure->un_select();
        selectedFigure->update();
    }
    mode = drawing;
}

Figure *Scene::figureAt(QPointF point)
{
    foreach (QGraphicsItem *item, this->items())
        if (item->shape().contains(point))
            return dynamic_cast<Figure *>(item);
    return nullptr;
}
void Scene::deleteSelectedFigure()
{
    if (selectedFigure != nullptr && selectedFigure->is_selected())
    {
        this->removeItem(selectedFigure);
        delete selectedFigure;
        selectedFigure = nullptr;
    }
    this->update(QRectF(0, 0, this->width(), this->height()));
}

qreal Scene::getSelectedFigurePerimeter(bool &ok)
{
    ok = true;
    if (selectedFigure != nullptr && selectedFigure->is_selected())
        return selectedFigure->getPerimeter();
    ok = false;
    return 0;
}

qreal Scene::getSelectedFigureSquare(bool &ok)
{
    ok = true;
    if (selectedFigure != nullptr && selectedFigure->is_selected())
        return selectedFigure->getSquare();
    ok = false;
    return 0;
}

void Scene::removeAllItems()
{
    selectedFigure = nullptr;
    clear();
    update(QRectF(0, 0, width(), height()));
}

bool Scene::onRectBoard(QRectF rect, QPointF point, int &side)
{
    side = -1;
    qreal offset = 30;
    if ((rect.contains(point) && (!rect.contains(QPointF(point.x() + offset, point.y())) || !rect.contains(QPointF(point.x() - offset, point.y())) || !rect.contains(QPointF(point.x(), point.y() + offset)) || !rect.contains(QPointF(point.x(), point.y() - offset)))) ||
        (!rect.contains(point) && (rect.contains(QPointF(point.x() + offset, point.y())) || rect.contains(QPointF(point.x() - offset, point.y())) || rect.contains(QPointF(point.x(), point.y() + offset)) || rect.contains(QPointF(point.x(), point.y() - offset)))))
    {
        if ((rect.contains(point) && !rect.contains(QPointF(point.x(), point.y() - offset))) || (!rect.contains(point) && rect.contains(QPointF(point.x(), point.y() + offset))))
            side = 0;
        if ((rect.contains(point) && !rect.contains(QPointF(point.x() + offset, point.y()))) || (!rect.contains(point) && rect.contains(QPointF(point.x() - offset, point.y()))))
            side = 1;
        if ((rect.contains(point) && !rect.contains(QPointF(point.x(), point.y() + offset))) || (!rect.contains(point) && rect.contains(QPointF(point.x(), point.y() - offset))))
            side = 2;
        if ((rect.contains(point) && !rect.contains(QPointF(point.x() - offset, point.y()))) || (!rect.contains(point) && rect.contains(QPointF(point.x() + offset, point.y()))))
            side = 3;
        return true;
    }
    return false;
}

void Scene::un_select()
{
    if (selectedFigure != nullptr && selectedFigure->is_selected())
    {
        selectedFigure->un_select();
        selectedFigure->update();
    }
}
