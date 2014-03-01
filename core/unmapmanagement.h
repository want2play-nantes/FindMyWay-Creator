#ifndef UNMAPMANAGEMENT_H
#define UNMAPMANAGEMENT_H

#include <QtXml>

#include "core/map.h"
#include "core/node.h"
#include "core/link.h"

//#include "core/nodes/classroom.h"

class Map;
class Node;
class Link;

class UnmapManagement
{
public:
    static bool saveMap(Map *map, QString path);
    static Map* openMap(QString path);

private:
    UnmapManagement();

    static Map* loadXml(QDomDocument *datas);
    static QDomDocument *createXml(Map *map);
};

#endif // UNMAPMANAGEMENT_H
