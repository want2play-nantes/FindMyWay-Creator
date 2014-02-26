#include "graphicscene.h"
#include <iostream>
#include <QMimeData>
#include <QLabel>
#include <QMessageBox>
#include <QImage>
#include <QString>
#include <stdio.h>
#include <stdlib.h>
#include <QApplication>
#include <QDebug>




using namespace std;

Graphicscene::Graphicscene(QString filePath) :
    QGraphicsScene()
{

    mFilePath = QString();
    initializeImage();

    QPainter *painter = new QPainter(mImage);
    painter->fillRect(0, 0, mImage->width(), mImage->height(), Qt::white);
    painter->end();

    mFilePath = QString();
    mFilePath = filePath;
     QImage layer(mFilePath);
    setSceneRect(QRectF(0, 0, layer.width(),layer.height()));
     //mFilePath = QString("");

    //open(filePath);

}


void Graphicscene::initializeImage()
{
    mImage = new QImage(QSize(400, 300), QImage::Format_ARGB32_Premultiplied);
}

void Graphicscene::open(const QString &filePath)
{
    QApplication::setOverrideCursor(Qt::WaitCursor);

    if(mImage->load(filePath))
    {
        *mImage = mImage->convertToFormat(QImage::Format_ARGB32_Premultiplied);
        mFilePath = filePath;
        mLastFilePath = filePath;
        QPainter *painter = new QPainter(mImage);
        painter->fillRect(0, 0, mImage->rect().right() + 6, mImage->rect().bottom() + 6, Qt::white);
       painter->end();
        QApplication::restoreOverrideCursor();
    }
    else
    {
        qDebug()<<QString("Can't open file %1").arg(filePath);
        QApplication::restoreOverrideCursor();
      //  QMessageBox::warning(this, tr("Error opening file"), tr("Can't open file \"%1\".").arg(filePath));
    }
}

void Graphicscene::dragEnterEvent ( QGraphicsSceneDragDropEvent * event ){


    if(this->sceneRect().contains(event->scenePos())){

        event->accept();

    }else {

        event->ignore();

    }

}
void Graphicscene::dragLeaveEvent ( QGraphicsSceneDragDropEvent * event ){


    QGraphicsScene::dragLeaveEvent(event);

    event->accept();

}

void Graphicscene::dragMoveEvent ( QGraphicsSceneDragDropEvent * event ){


    event->accept();

}

void Graphicscene::dropEvent ( QGraphicsSceneDragDropEvent * event ){

    if ((event->mimeData()->hasFormat("application/x-dnditemdata")) && (this->sceneRect().contains(event->scenePos()) == true)) {
        QByteArray itemData = event->mimeData()->data("application/x-dnditemdata");
        QDataStream dataStream(&itemData, QIODevice::ReadOnly);

std::cout << "Position %f",event->pos().x();
        QPixmap pixmap;
        QPoint offset;
        int type;
        dataStream >> pixmap >> offset >> type;

        std::cout << type;
        printf("\nType :%d",type);

        //Peut etre utilisé pour la création des classes coeur(Classroom,Door,Corridor...)
        switch(type){

        case 1 :
            //tempGraphicComponent = new GraphicClassroomComponent(pixmap,type);
            tempGraphicComponent->setPos(event->scenePos());;
            break;

        default:
            tempGraphicComponent = new Graphicwidget(pixmap,type);
            //testPixmap = new GraphicComponent(pixmap);
            tempGraphicComponent->setPos(event->scenePos());;

        }

        addItem(tempGraphicComponent);
        event->accept();

    } else {

        event->ignore();
        QMessageBox msgBox;
        msgBox.setWindowTitle("Drop components issues");
        msgBox.setText("This component can't be received by the editing view.");
        msgBox.setInformativeText("We advice you to choose another one and try again.");
        msgBox.setStandardButtons(QMessageBox::Cancel);
        msgBox.setDefaultButton(QMessageBox::Cancel);
        msgBox.exec();
    }


}

void Graphicscene::drawBackground ( QPainter * painter, const QRectF & rect ){

    painter->setPen(Qt::black);
    painter->setBackgroundMode(Qt::OpaqueMode);
    painter->drawPixmap(QPoint(0,0),QPixmap(mFilePath));

}

void Graphicscene::deleteComponents(){

    QList<QGraphicsItem*> *itemsSelected = new QList<QGraphicsItem*>();
    *itemsSelected = this->selectedItems();

    //Boucle pour la suppression de tous les éléments de la liste
    if(!(itemsSelected->isEmpty())){

        this->removeItem(itemsSelected->first());


        QMessageBox msgBox;
        msgBox.setWindowTitle("Delete results");
        msgBox.setText("The selected component had been removed of editing view.");
        //msgBox.setInformativeText("We advice you to choose another one and try again.");
        msgBox.setStandardButtons(QMessageBox::Cancel);
        msgBox.setDefaultButton(QMessageBox::Cancel);
        msgBox.exec();


    }else {

        QMessageBox msgBox;
        msgBox.setWindowTitle("Delete results");
        msgBox.setText("Nothing to remove.");
        msgBox.setInformativeText("Please select a item and try again.");
        msgBox.setStandardButtons(QMessageBox::Cancel);
        msgBox.setDefaultButton(QMessageBox::Cancel);
        msgBox.exec();

    }

}

QString Graphicscene::getLayerFile() const
{
    return mFilePath;
}

void Graphicscene::setLayerFile(const QString &value)
{
    mFilePath = value;
}
