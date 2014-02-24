#include <QPainter>
#include <QPaintEvent>
#include <QImage>

#include "imagepreview.h"

ImagePreview::ImagePreview(QImage *image, QWidget *parent) :
    QWidget(parent)
{
    mImage = image;
}

void ImagePreview::paintEvent(QPaintEvent *event)
{
    if(mImage)
    {
        QPainter *painter = new QPainter(this);

        painter->drawImage(event->rect(), *mImage, event->rect());

        painter->end();
    }
}
