#ifndef GRAPHICVIEW_H
#define GRAPHICVIEW_H


#include <QGraphicsView>
#include <QDragEnterEvent>
#include <QDragLeaveEvent>
#include <QDropEvent>

        class GraphicView : public QGraphicsView
        {
            Q_OBJECT
        public:
            explicit GraphicView(QGraphicsScene *scene);



        signals:

        public slots:

        };


#endif // GRAPHICVIEW_H
