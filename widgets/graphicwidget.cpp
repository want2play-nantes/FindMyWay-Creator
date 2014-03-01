
#include "graphicwidget.h"

GraphicWidget::GraphicWidget(QPixmap img) :
    pen(),

    width(img.width()),
    height(img.height()),

    img(img)
{
    pen.setWidth(1);
    pen.setColor(Qt::black);
    pen.setStyle(Qt::SolidLine);

    setAcceptDrops(true);
    setFlag(QGraphicsItem::ItemIsSelectable, true);
    setFlag(QGraphicsItem::ItemIsMovable);
}

QRectF GraphicWidget::boundingRect() const
{
    return QRect(0, 0, width, height);
}

void GraphicWidget::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    painter->setPen(pen);

    QPointF topLeft (0, 0);
    QPointF bottomRight (width , height);

    QRectF rect (topLeft, bottomRight);

    painter->drawPixmap(rect.toRect(), img);

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
