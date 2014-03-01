#ifndef FINALNODE_H
#define FINALNODE_H

#include "node.h"

class FinalNode : public Node
{
public:
    FinalNode(Map *map, int x, int y, int type, QPixmap *img);
};

#endif // FINALNODE_H
