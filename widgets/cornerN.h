#ifndef CORNERN_H
#define CORNERN_H

#include <QObject>
#include <QGraphicsItem>
#include <QGraphicsRectItem>
#include <QGraphicsTextItem>
#include <QGraphicsSceneHoverEvent>
#include <QGraphicsSceneMouseEvent>
#include <QColor>
#include <QPainter>
#include <QPen>
#include <QPointF>



class cornerN : public QGraphicsItem
{

public:
    explicit cornerN(QGraphicsItem *parent = 0,  int corner=0);

    int  getCorner();
    void setMouseState(int);
    int  getMouseState();

    qreal mouseDownX;
    qreal mouseDownY;

     enum {kMouseReleased=0, kMouseDown, kMouseMoving};



private:

    virtual QRectF boundingRect() const;
    virtual void paint (QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    virtual void hoverEnterEvent ( QGraphicsSceneHoverEvent * event );
    virtual void hoverLeaveEvent ( QGraphicsSceneHoverEvent * event );


    virtual void mouseMoveEvent(QGraphicsSceneDragDropEvent *event);

    virtual void mousePressEvent(QGraphicsSceneDragDropEvent *event);
    virtual void mouseReleaseEvent (QGraphicsSceneMouseEvent * event );

    QColor _outterborderColor;
    QPen _outterborderPen;

    qreal   _width;
    qreal   _height;

    int _corner;


    int _mouseButtonState;


};

#endif // CORNER_H
