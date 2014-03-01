#ifndef GRAPHICWIDGET_H
#define GRAPHICWIDGET_H

#include <QGraphicsWidget>
#include <QPainter>
#include <QPen>

using namespace std;

class GraphicWidget : public QGraphicsWidget
{
    Q_OBJECT
public:
    GraphicWidget(QPixmap img);

protected:
    virtual QRectF boundingRect() const;
    virtual void paint (QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

    QPixmap img;
    QPen pen;

    int width, height;

    int drawingWidth, drawingHeight;
    int drawingOriginX, drawingOriginY;
};

#endif // GRAPHICWIDGET_H
