#include <QtGui>

#include "dragwidget.h"
#include<QVBoxLayout>


DragWidget::DragWidget(QWidget *parent)
    : QFrame(parent)
{
#if defined(Q_OS_SYMBIAN) || defined(Q_WS_MAEMO_5) || defined(Q_WS_SIMULATOR)
#else
    //setMinimumSize(150, 500);
#endif
    //setFrameStyle(QFrame::Sunken | QFrame::StyledPanel);
    setAcceptDrops(false);
    QVBoxLayout *conteneur = new QVBoxLayout;

    QLabel *boatIcon = new QLabel(this);
        boatIcon->setPixmap(QPixmap(":/logos/logos/salle.png"));
        boatIcon->move(0, 50);
        boatIcon->show();
        boatIcon->setAttribute(Qt::WA_DeleteOnClose);

        QLabel *boatIcontext = new QLabel(this);
        boatIcontext->show();
        boatIcontext->move(0, 50);
        boatIcontext->setText("salle");

        QLabel *carIcon = new QLabel(this);
        carIcon->setPixmap(QPixmap(":/logos/logos/escalier.png"));
        carIcon->move(0, 60);
        carIcon->show();
        carIcon->setAttribute(Qt::WA_DeleteOnClose);


        QLabel *boatIcontext2 = new QLabel(this);
        boatIcontext2->show();
        boatIcontext2->move(0, 50);
        boatIcontext2->setText("escalier");

        QLabel *houseIcon = new QLabel(this);
        houseIcon->setPixmap(QPixmap(":/logos/logos/porte.png"));
        houseIcon->move(0, 150);
        houseIcon->show();
        houseIcon->setAttribute(Qt::WA_DeleteOnClose);

        QLabel *boatIcontext3 = new QLabel(this);
        boatIcontext3->show();
        boatIcontext3->move(0, 150);
        boatIcontext3->setText("porte");

        QLabel *houseIcon2 = new QLabel(this);
        houseIcon2->setPixmap(QPixmap(":/logos/logos/ascenseur.png"));
        houseIcon2->move(0, 200);
        houseIcon2->show();
        houseIcon2->setAttribute(Qt::WA_DeleteOnClose);

        QLabel *boatIcontext4 = new QLabel(this);
        boatIcontext4->show();
        boatIcontext4->move(0, 200);
        boatIcontext4->setText("Ascenseur");

        QLabel *houseIcon3 = new QLabel(this);
        houseIcon3->setPixmap(QPixmap(":/logos/logos/portePrin.png"));
        houseIcon3->move(0, 200);
        houseIcon3->show();
        houseIcon3->setAttribute(Qt::WA_DeleteOnClose);

        QLabel *boatIcontext5 = new QLabel(this);
        boatIcontext5->show();
        boatIcontext5->move(0, 200);
        boatIcontext5->setText("porte principale");


        conteneur->addWidget(boatIcon,0,0);
        conteneur->addWidget(boatIcontext);
        conteneur->addWidget(carIcon);
        conteneur->addWidget(boatIcontext2);
        conteneur->addWidget(houseIcon);
        conteneur->addWidget(boatIcontext3);
        conteneur->addWidget(houseIcon2);
        conteneur->addWidget(boatIcontext4);
        conteneur->addWidget(houseIcon3);
        conteneur->addWidget(boatIcontext5);
         this->setLayout(conteneur);

}

void DragWidget::dragEnterEvent(QDragEnterEvent *event)
{
    if (event->mimeData()->hasFormat("application/x-dnditemdata")) {
        if (event->source() == this) {
            event->setDropAction(Qt::MoveAction);
            event->accept();
        } else {
            event->acceptProposedAction();
        }
    } else {
        event->ignore();
    }
}

void DragWidget::dragMoveEvent(QDragMoveEvent *event)
{
    if (event->mimeData()->hasFormat("application/x-dnditemdata")) {
        if (event->source() == this) {
            event->setDropAction(Qt::MoveAction);
            event->accept();
        } else {
            event->acceptProposedAction();
        }
    } else {
        event->ignore();
    }
}

void DragWidget::dropEvent(QDropEvent *event)
{
    if (event->mimeData()->hasFormat("application/x-dnditemdata")) {
        QByteArray itemData = event->mimeData()->data("application/x-dnditemdata");
        QDataStream dataStream(&itemData, QIODevice::ReadOnly);

        QPixmap pixmap;
        QPoint offset;
        dataStream >> pixmap >> offset;

        QLabel *newIcon = new QLabel(this);
        newIcon->setPixmap(pixmap);
        newIcon->move(event->pos() - offset);
        newIcon->show();
        newIcon->setAttribute(Qt::WA_DeleteOnClose);

        if (event->source() == this) {
            event->setDropAction(Qt::MoveAction);
            event->accept();
        } else {
            event->acceptProposedAction();
        }
    } else {
        event->ignore();
    }
}

void DragWidget::mousePressEvent(QMouseEvent *event)
{
    QLabel *child = static_cast<QLabel*>(childAt(event->pos()));
    if (!child)
        return;

    QPixmap pixmap = *child->pixmap();

    QByteArray itemData;
    QDataStream dataStream(&itemData, QIODevice::WriteOnly);
    dataStream << pixmap << QPoint(event->pos() - child->pos());

    QMimeData *mimeData = new QMimeData;
    mimeData->setData("application/x-dnditemdata", itemData);

    QDrag *drag = new QDrag(this);
    drag->setMimeData(mimeData);
    drag->setPixmap(pixmap);
    drag->setHotSpot(event->pos() - child->pos());

    QPixmap tempPixmap = pixmap;
    QPainter painter;
    painter.begin(&tempPixmap);
    painter.fillRect(pixmap.rect(), QColor(127, 127, 127, 127));
    painter.end();

    child->setPixmap(tempPixmap);

    if (drag->exec(Qt::CopyAction | Qt::MoveAction, Qt::CopyAction) == Qt::MoveAction)
        child->close();
    else {
        child->show();
        child->setPixmap(pixmap);
    }
}
