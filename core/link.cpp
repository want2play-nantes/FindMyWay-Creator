#include "link.h"

Link::Link(Map *map, Node *from, Node *to, int distance) :
    map(map),
    from(from),
    to(to),
    distance(distance)
{
    map->addEdge(this);
}

Map *Link::getMap() const { return map; }

Node *Link::getTo() const { return to; }
void Link::setTo(Node *value) { to = value; }

Node *Link::getFrom() const { return from; }
void Link::setFrom(Node *value) { from = value; }

int Link::getDistance() const { return distance; }
void Link::setDistance(int value) { distance = value; }
