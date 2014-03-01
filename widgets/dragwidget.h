#ifndef DRAGWIDGET_H
#define DRAGWIDGET_H

#include <QtGui>
#include <QGridLayout>
#include <QLabel>

class DragWidget : public QFrame
{
public:
    DragWidget(QWidget *parent=0);

protected:
    void dragEnterEvent(QDragEnterEvent *event);
    void dragMoveEvent(QDragMoveEvent *event);
    void dropEvent(QDropEvent *event);
    void mousePressEvent(QMouseEvent *event);

};

#endif
