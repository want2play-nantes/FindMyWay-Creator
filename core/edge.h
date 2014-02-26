#ifndef EDGE_H
#define EDGE_H

#include "node.h"

class Edge
{
public:
    Edge();

private:
    Node *from;
    Node *to;
    int distance;
};

#endif // EDGE_H
