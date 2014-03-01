#ifndef LINK_H
#define LINK_H

#include "map.h"
#include "node.h"

class Map;
class Node;

class Link
{
public:
    Link(Map *map, Node *from, Node *to, int distance);

    Map *getMap() const;

    Node *getFrom() const;
    void setFrom(Node *value);

    Node *getTo() const;
    void setTo(Node *value);

    int getDistance() const;
    void setDistance(int value);

private:
    Map *map;
    Node *from;
    Node *to;
    int distance;
};

#endif // LINK_H
