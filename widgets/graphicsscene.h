#ifndef GRAPHICSCENE_H
#define GRAPHICSCENE_H

#include <QGraphicsScene>
#include <QGraphicsSceneDragDropEvent>

#include "widgets/graphicwidget.h"

#include "core/map.h"

class GraphicsScene : public QGraphicsScene
{
    Q_OBJECT
public:
    explicit GraphicsScene(Map *map);
    GraphicWidget *tempGraphicComponent;

    Map *getMap() const;
    void setMap(Map *value);

protected:
    virtual void dragEnterEvent (QGraphicsSceneDragDropEvent * event);
    virtual void dragLeaveEvent (QGraphicsSceneDragDropEvent * event);
    virtual void dragMoveEvent (QGraphicsSceneDragDropEvent * event);
    virtual void dropEvent (QGraphicsSceneDragDropEvent * event);
    virtual void drawBackground (QPainter * painter, const QRectF & rect);

    virtual void keyPressEvent(QKeyEvent *keyEvent);

private:
    Map *map;

public slots:
    void deleteSelectedItems();

};

#endif // GRAPHICSCENE_H
