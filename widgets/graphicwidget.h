#ifndef GRAPHICWIDGET_H
#define GRAPHICWIDGET_H

#include <QGraphicsObject>
#include <QGraphicsSceneHoverEvent>
#include <QGraphicsSceneMouseEvent>
#include <QColor>
#include <QString>
#include <QPainter>
#include <QPen>
#include <QPointF>
#include <QStyleOptionGraphicsItem>
#include <QPixmap>
#include "cornerN.h"

using namespace std;

class Graphicwidget : public QGraphicsObject
{
    Q_OBJECT
public:
    Graphicwidget(QPixmap pM, int type);

protected:
    virtual QRectF boundingRect() const; ///< must be re-implemented in this class to provide the diminsions of the box to the QGraphicsView
    virtual void paint (QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget); ///< must be re-implemented here to pain the box on the paint-event
    virtual void hoverEnterEvent ( QGraphicsSceneHoverEvent * event ); ///< must be re-implemented to handle mouse hover enter events
    virtual void hoverLeaveEvent ( QGraphicsSceneHoverEvent * event ); ///< must be re-implemented to handle mouse hover leave events
    virtual void mouseMoveEvent(QGraphicsSceneDragDropEvent *event);
    virtual void mousePressEvent(QGraphicsSceneDragDropEvent *event);
    virtual bool sceneEventFilter ( QGraphicsItem * watched, QEvent * event ) ;

    void setCornerPositions();
    void adjustSize(int x, int y);

    QPixmap pixM;
    QColor _outterborderColor; ///< the hover event handlers will toggle this between red and black
    QPen _outterborderPen; ///< the pen is used to paint the red/black border
    QPointF _location;
    QPointF _dragStart;
    int     _gridSpace;
    qreal   _width;
    qreal   _height;

    QPointF _cornerDragStart;

    int _XcornerGrabBuffer;
    int _YcornerGrabBuffer;
    qreal   _drawingWidth;
    qreal   _drawingHeight;
    qreal   _drawingOrigenX;
    qreal   _drawingOrigenY;
    /**
     * @brief _corners
     *@yoann : tu peur recupérer les 4 coter du widget !
     */
    cornerN * _corners[4];

    int type;



signals:

public slots:

};

#endif // GRAPHICWIDGET_H
