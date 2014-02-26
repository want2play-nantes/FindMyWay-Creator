#ifndef GRAPHICSCENE_H
#define GRAPHICSCENE_H

#include "widgets/graphicwidget.h"



#include <QGraphicsScene>
#include <QGraphicsSceneDragDropEvent>
#include <QGraphicsItem>
#include <QPainter>
#include <QRect>
#include <QString>

class Graphicscene : public QGraphicsScene
{
    Q_OBJECT
public:
    explicit Graphicscene(QString filePath);
    Graphicwidget *tempGraphicComponent;
    QList<QGraphicsItem> *allComponentContains;


    QString getLayerFile() const;
    void setLayerFile(const QString &value);
    void open(const QString &filePath);
    void initializeImage();
protected:
    virtual void dragEnterEvent ( QGraphicsSceneDragDropEvent * event );
   virtual void dragLeaveEvent ( QGraphicsSceneDragDropEvent * event );
    virtual void dragMoveEvent ( QGraphicsSceneDragDropEvent * event );
    virtual void dropEvent ( QGraphicsSceneDragDropEvent * event );
    virtual void 	drawBackground ( QPainter * painter, const QRectF & rect );
signals:

private:
    QString mFilePath,mLastFilePath;
     QImage *mImage;  /**< Main image. */


public slots:
    void deleteComponents();

};

#endif // GRAPHICSCENE_H
