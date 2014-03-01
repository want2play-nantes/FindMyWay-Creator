
#include "graphicsscene.h"

using namespace std;

GraphicsScene::GraphicsScene(Map * map) : QGraphicsScene(), map(map)
{
    setSceneRect(QRectF(0, 0, map->getImg()->width(),map->getImg()->height()));
}

Map *GraphicsScene::getMap() const
{
    return map;
}

void GraphicsScene::setMap(Map *value)
{
    map = value;
}

void GraphicsScene::dragEnterEvent (QGraphicsSceneDragDropEvent * event)
{
    event->acceptProposedAction();
}
void GraphicsScene::dragLeaveEvent (QGraphicsSceneDragDropEvent * event)
{
    event->acceptProposedAction();
}

void GraphicsScene::dragMoveEvent (QGraphicsSceneDragDropEvent * event)
{
    event->acceptProposedAction();
}

void GraphicsScene::dropEvent (QGraphicsSceneDragDropEvent * event)
{

    if ((event->mimeData()->hasFormat("application/x-dnditemdata")) && (this->sceneRect().contains(event->scenePos())))
    {
        qDebug() << "Objet dropper";

        QByteArray itemData = event->mimeData()->data("application/x-dnditemdata");
        QDataStream dataStream(&itemData, QIODevice::ReadOnly);

        QPixmap pixmap;
        QPoint offset;

        dataStream >> pixmap >> offset;

        tempGraphicComponent = new GraphicWidget(pixmap);
        tempGraphicComponent->setPos(event->scenePos() - offset);
        addItem(tempGraphicComponent);

        event->accept();
    }
    else {
        event->ignore();
    }
}

void GraphicsScene::drawBackground (QPainter * painter, const QRectF & rect)
{
    painter->setPen(Qt::black);
    painter->setBackgroundMode(Qt::OpaqueMode);
    painter->drawPixmap(QPoint(0,0), *map->getImg());
}

void GraphicsScene::keyPressEvent (QKeyEvent * keyEvent)
{
    if (keyEvent->matches(QKeySequence::Delete)) {
        deleteSelectedItems();
    }
}

void GraphicsScene::deleteSelectedItems()
{
    while (selectedItems().count() > 0)
    {
        removeItem(selectedItems().first());
    }
}
