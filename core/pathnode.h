#ifndef PATHNODE_H
#define PATHNODE_H

#include "node.h"

class PathNode : public Node
{
public:
    PathNode(Map *map, int x, int y, int type, QPixmap *img);
};

#endif // PATHNODE_H
