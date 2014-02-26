#include "cornerN.h"


cornerN::cornerN(QGraphicsItem *parent,  int corner) :
    QGraphicsItem(parent),
    mouseDownX(0),
    mouseDownY(0),
    _outterborderColor(Qt::blue),
    _outterborderPen(),
    _width(6),
    _height(6),
    _corner(corner),
    _mouseButtonState(kMouseReleased)
{
    setParentItem(parent);

    _outterborderPen.setWidth(2);
    _outterborderPen.setColor(_outterborderColor);

   this->setAcceptHoverEvents(true);
}

void cornerN::setMouseState(int s)
{
    _mouseButtonState = s;
}

int cornerN::getMouseState()
{
    return _mouseButtonState;
}

int cornerN::getCorner()
{
    return _corner;
}


void cornerN::mouseMoveEvent(QGraphicsSceneDragDropEvent *event)
{
    event->setAccepted(false);
}

void cornerN::mousePressEvent(QGraphicsSceneDragDropEvent *event)
{
    event->setAccepted(false);
}

void cornerN::mouseReleaseEvent ( QGraphicsSceneMouseEvent * event )
{
    event->setAccepted(true);
}


void cornerN::hoverLeaveEvent ( QGraphicsSceneHoverEvent * )
{
    _outterborderColor = Qt::blue;
    this->update(0,0,_width,_height);
}

void cornerN::hoverEnterEvent ( QGraphicsSceneHoverEvent * )
{
    _outterborderColor = Qt::green;
    this->update(0,0,_width,_height);
}

QRectF cornerN::boundingRect() const
{
    return QRectF(0,0,_width,_height);
}


void cornerN::paint (QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *)
{


    _outterborderPen.setCapStyle(Qt::RoundCap);
    _outterborderPen.setStyle(Qt::SolidLine);
    painter->setPen(_outterborderPen);

    QPointF topLeft (0, 0);
    QPointF bottomRight ( _width, _height);

    QRectF rect (topLeft, bottomRight);

    QBrush brush (Qt::SolidPattern);
    brush.setColor (_outterborderColor);
    painter->fillRect(rect,brush);

}
