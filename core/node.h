#ifndef NODE_H
#define NODE_H

#include <QtGui>

#include "map.h"
#include "link.h"

class Map;
class Link;

class Node
{
public:
    Node(Map *map, int x, int y, int type, QPixmap *img);

    int getId() const;
    void setId(int value);

    Map *getMap() const;
    QPixmap *getImg() const;

    int getX() const;
    void setX(int value);

    int getY() const;
    void setY(int value);

    int getType() const;

    QList<Link *> *getChildren() const;

    /**
     * @brief link Lie 2 noeuds entre eux
     * @param from noeud d'arrivée
     * @return noeud d'arrivée (permet de lier facilement à la chaîne)
     */
    Node *link(Node *to, int distance);

protected:
    int id;
    int type; // A transformer en énumeration
    Map *map;
    QPixmap *img;
    int x, y;
    QList<Link*> *children;
};

#endif // NODE_H
