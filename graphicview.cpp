#include "graphicview.h"

#include <QGraphicsItem>
#include <QImage>

GraphicView::GraphicView(QGraphicsScene* scene) :
    QGraphicsView(scene)
{

   this->setAcceptDrops(true);
   this->setAlignment (Qt::AlignLeft | Qt::AlignTop);
   this->setRenderHint(QPainter::Antialiasing);

}

