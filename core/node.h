#ifndef NODE_H
#define NODE_H

#include <QtGui>

class Node
{
public:
    Node();


protected:
    QImage *img;
    int x, y;
    QList<Node*> *children;
};

#endif // NODE_H
