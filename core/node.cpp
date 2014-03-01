#include "node.h"

Node::Node(Map *map, int x, int y, int type, QPixmap *img) :
    map(map),
    x(x),
    y(y),
    type(type),
    img(img)
{
    children = new QList<Link*>();
    map->addNode(this);
}

int Node::getId() const { return id; }
void Node::setId(int value) { id = value; }

Map *Node::getMap() const { return map; }
QPixmap *Node::getImg() const { return img; }

int Node::getX() const { return x; }
void Node::setX(int value) { x = value; }

int Node::getY() const { return y; }
void Node::setY(int value) { y = value; }

int Node::getType() const { return type; }

QList<Link *> *Node::getChildren() const { return children; }

Node *Node::link(Node *to, int distance)
{
    Link * link = new Link(map, this, to, distance);

    this->children->append(link);
    to->getChildren()->append(link);

    return to;
}
