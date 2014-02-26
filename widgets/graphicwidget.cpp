#include "graphicwidget.h"
#include <iostream>
#include <QDebug>
#include <QGraphicsPixmapItem>

#include "math.h"

Graphicwidget::Graphicwidget(QPixmap image,int type):
    _outterborderColor(Qt::black),
    _outterborderPen(),
    _location(0,0),
    _dragStart(0,0),
    _width(qreal(image.width())*2),
    _height(qreal(image.height())*2),
    _cornerDragStart(0,0),
    _XcornerGrabBuffer(20),
    _YcornerGrabBuffer(20),
    _drawingWidth(_width - _XcornerGrabBuffer),
    _drawingHeight(_height - _YcornerGrabBuffer),
    _drawingOrigenX(_XcornerGrabBuffer),
    _drawingOrigenY(_YcornerGrabBuffer),
    pixM(image),
    type(type)
{
    _outterborderPen.setWidth(2);
    _outterborderPen.setColor(_outterborderColor);

    setAcceptDrops(true);
    this->setAcceptHoverEvents(true);
    setFlag(QGraphicsItem::ItemIsSelectable,true);
    setFlag(QGraphicsItem::ItemIsMovable);


}

void Graphicwidget::adjustSize(int x, int y)
{
    _width += x;
    _height += y;

    _drawingWidth =  _width - _XcornerGrabBuffer;
    _drawingHeight=  _height - _YcornerGrabBuffer;
}


bool Graphicwidget::sceneEventFilter ( QGraphicsItem * watched, QEvent * event )
{
    qDebug() << " QEvent == " + QString::number(event->type());

    cornerN * corner = dynamic_cast<cornerN *>(watched);
    if ( corner == NULL) return false; // not expected to get here

    QGraphicsSceneMouseEvent * mevent = dynamic_cast<QGraphicsSceneMouseEvent*>(event);
    if ( mevent == NULL)
    {
        // this is not one of the mouse events we are interrested in
        return false;
    }


    switch (event->type() )
    {
            // if the mouse went down, record the x,y coords of the press, record it inside the corner object
        case QEvent::GraphicsSceneMousePress:
            {
                corner->setMouseState(cornerN::kMouseDown);
                corner->mouseDownX = mevent->pos().x();
                corner->mouseDownY = mevent->pos().y();
            }
            break;

        case QEvent::GraphicsSceneMouseRelease:
            {
                corner->setMouseState(cornerN::kMouseReleased);

            }
            break;

        case QEvent::GraphicsSceneMouseMove:
            {
                corner->setMouseState(cornerN::kMouseMoving );
            }
            break;

        default:
            // we dont care about the rest of the events
            return false;
            break;
    }


    if ( corner->getMouseState() == cornerN::kMouseMoving )
    {

        qreal x = mevent->pos().x(), y = mevent->pos().y();

        // depending on which corner has been grabbed, we want to move the position
        // of the item as it grows/shrinks accordingly. so we need to eitehr add
        // or subtract the offsets based on which corner this is.

        int XaxisSign = 0;
        int YaxisSign = 0;
        switch( corner->getCorner() )
        {
        case 0:
            {
                XaxisSign = +1;
                YaxisSign = +1;
            }
            break;

        case 1:
            {
                XaxisSign = -1;
                YaxisSign = +1;
            }
            break;

        case 2:
            {
                XaxisSign = -1;
                YaxisSign = -1;
            }
            break;

        case 3:
            {
                XaxisSign = +1;
                YaxisSign = -1;
            }
            break;

        }

        // if the mouse is being dragged, calculate a new size and also re-position
        // the box to give the appearance of dragging the corner out/in to resize the box

        int xMoved = corner->mouseDownX - x;
        int yMoved = corner->mouseDownY - y;

        int newWidth = _width + ( XaxisSign * xMoved);
        if ( newWidth < 40 ) newWidth  = 40;

        int newHeight = _height + (YaxisSign * yMoved) ;
        if ( newHeight < 40 ) newHeight = 40;

        int deltaWidth  =   newWidth - _width ;
        int deltaHeight =   newHeight - _height ;

        adjustSize(  deltaWidth ,   deltaHeight);

        deltaWidth *= (-1);
        deltaHeight *= (-1);

        if ( corner->getCorner() == 0 )
        {
            int newXpos = this->pos().x() + deltaWidth;
            int newYpos = this->pos().y() + deltaHeight;
            this->setPos(newXpos, newYpos);
        }
        else   if ( corner->getCorner() == 1 )
        {
            int newYpos = this->pos().y() + deltaHeight;
            this->setPos(this->pos().x(), newYpos);
        }
        else   if ( corner->getCorner() == 3 )
        {
            int newXpos = this->pos().x() + deltaWidth;
            this->setPos(newXpos,this->pos().y());
        }

        setCornerPositions();

        this->update();
    }

    return true;// true => do not send event to watched - we are finished with this event
}



QRectF Graphicwidget::boundingRect() const
{
    /*qreal radius = _outterborderPen.width()/2; //Create a gap of the pen half
    qreal factor = 2;
    return QRect(-radius,-radius, _width+(factor*radius), _height+(factor*radius));*/
    return QRect(0,0, _width, _height);

}

void Graphicwidget::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{

    /*if (option->state & QStyle::State_Selected)*/

   _outterborderPen.setStyle(Qt::SolidLine);
   painter->setPen(_outterborderPen);

   QPointF topLeft (_drawingOrigenX,_drawingOrigenX);
   QPointF bottomRight ( _drawingWidth , _drawingHeight);

   QRectF rect (topLeft, bottomRight);

   painter->drawPixmap(rect.toRect(),this->pixM);


   if(isSelected())
       {
           QPen selectedPen;
           selectedPen.setColor(Qt::red);
           selectedPen.setWidth(1);
           selectedPen.setStyle(Qt::DashLine);
           painter->setPen(selectedPen);
           painter->drawRect(rect);
       }

}



// remove the corner grabbers

void Graphicwidget::hoverLeaveEvent ( QGraphicsSceneHoverEvent * )
{
    _outterborderColor = Qt::black;

    _corners[0]->setParentItem(NULL);
    _corners[1]->setParentItem(NULL);
    _corners[2]->setParentItem(NULL);
    _corners[3]->setParentItem(NULL);

    delete _corners[0];
    delete _corners[1];
    delete _corners[2];
    delete _corners[3];
}

// create the corner grabbers

void Graphicwidget::hoverEnterEvent ( QGraphicsSceneHoverEvent * )
{
    _outterborderColor = Qt::red;

    _corners[0] = new cornerN(this,0);
    _corners[1] = new cornerN(this,1);
    _corners[2] = new cornerN(this,2);
    _corners[3] = new cornerN(this,3);


    _corners[0]->installSceneEventFilter(this);
    _corners[1]->installSceneEventFilter(this);
    _corners[2]->installSceneEventFilter(this);
    _corners[3]->installSceneEventFilter(this);

    setCornerPositions();

}

void Graphicwidget::setCornerPositions()
{
    /*_corners[0]->setPos(_drawingOrigenX, _drawingOrigenY);
    _corners[1]->setPos(_drawingWidth,  _drawingOrigenY);
    _corners[2]->setPos(_drawingWidth , _drawingHeight);
    _corners[3]->setPos(_drawingOrigenX, _drawingHeight);*/

    _corners[0]->setPos(_drawingOrigenX, _drawingOrigenY);
    _corners[1]->setPos((_drawingWidth-6),  _drawingOrigenY);
    _corners[2]->setPos((_drawingWidth-6) , (_drawingHeight-6));
    _corners[3]->setPos(_drawingOrigenX, (_drawingHeight-6));
}

void Graphicwidget::mouseMoveEvent(QGraphicsSceneDragDropEvent *event)
{
  event->setAccepted(true);
}

void Graphicwidget::mousePressEvent(QGraphicsSceneDragDropEvent *event)
{
    event->setAccepted(true);
}

