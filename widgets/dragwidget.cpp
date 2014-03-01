
#include "dragwidget.h"

DragWidget::DragWidget(QWidget *parent) : QFrame(parent)
{
    setAcceptDrops(false);

    QGridLayout *gridLayout = new QGridLayout;

    QLabel *classroomIcon = new QLabel(this);
    classroomIcon->setPixmap(QPixmap(":/logos/logos/salle.png"));
    QLabel *classroomLabel = new QLabel("Salle de cours", this);

    QLabel *stairsIcon = new QLabel(this);
    stairsIcon->setPixmap(QPixmap(":/logos/logos/escalier.png"));
    QLabel *stairsLabel = new QLabel("Escalier", this);

    QLabel *doorIcon = new QLabel(this);
    doorIcon->setPixmap(QPixmap(":/logos/logos/porte.png"));
    QLabel *doorLabel = new QLabel("Porte", this);

    QLabel *elevatorIcon = new QLabel(this);
    elevatorIcon->setPixmap(QPixmap(":/logos/logos/ascenseur.png"));
    QLabel *elevatorLabel = new QLabel("Ascenseur", this);

    QLabel *mainDoorIcon = new QLabel(this);
    mainDoorIcon->setPixmap(QPixmap(":/logos/logos/portePrin.png"));
    QLabel *mainDoorLabel = new QLabel("Porte principale", this);


    gridLayout->addWidget(classroomIcon, 0, 0);
    gridLayout->addWidget(classroomLabel, 0, 1);

    gridLayout->addWidget(stairsIcon, 1, 0);
    gridLayout->addWidget(stairsLabel, 1, 1);

    gridLayout->addWidget(doorIcon, 2, 0);
    gridLayout->addWidget(doorLabel, 2, 1);

    gridLayout->addWidget(elevatorIcon, 3, 0);
    gridLayout->addWidget(elevatorLabel, 3, 1);

    gridLayout->addWidget(mainDoorIcon, 4, 0);
    gridLayout->addWidget(mainDoorLabel, 4, 1);

    setLayout(gridLayout);

}

void DragWidget::dragEnterEvent(QDragEnterEvent *event)
{
    qDebug()<<"dragEnterEvent";

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
    qDebug()<<"dragMoveEvent";

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
    if (event->mimeData()->hasFormat("application/x-dnditemdata"))
    {
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
        }
        else {
            event->acceptProposedAction();
        }
    }
    else {
        event->ignore();
    }
}

void DragWidget::mousePressEvent(QMouseEvent *event)
{
    QLabel *child = static_cast<QLabel*>(childAt(event->pos()));
    if (!child || !child->pixmap())
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
