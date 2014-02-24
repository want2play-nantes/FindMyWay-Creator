#ifndef DRAGWIDGET_H
#define DRAGWIDGET_H

#include <QToolBar>
#include <QLabel>
class QDragEnterEvent;
class QDropEvent;

class DragWidget : public QToolBar
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
