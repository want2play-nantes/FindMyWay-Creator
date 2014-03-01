
#include "map.h"
#include "unmapmanagement.h"

Map::Map (QPixmap *img, QString fileName, int ufrRef, int building, int floor, int part) :
    img(img),
    fileName(fileName),
    ufrRef(ufrRef),
    building(building),
    floor(floor),
    part(part),
    changed(true),
    currentNodeId(0),
    loading(false)
{
    nodes = new QList<Node*>();
    links = new QList<Link*>();
}

// Getters et Setters

QPixmap* Map::getImg() const { return img; }

void Map::setImg(QPixmap *value) { img = value; }

int Map::getPart() const { return part; }
void Map::setPart(int value) { part = value; }

int Map::getFloor() const { return floor; }
void Map::setFloor(int value) { floor = value; }

int Map::getBuilding() const { return building; }
void Map::setBuilding(int value) { building = value; }

int Map::getUfrRef() const { return ufrRef; }
void Map::setUfrRef(int value) { ufrRef = value; }

QString Map::getFilePath() const { return filePath; }
void Map::setFilePath(QString value) { filePath = value; }

QString Map::getFileName() const { return fileName; }
void Map::setFileName(const QString &value) { fileName = value; }

bool Map::getChanged() const { return changed; }
void Map::setChanged(bool value) { changed = value; }

int Map::getCurrentNodeId() const { return currentNodeId; }
void Map::setCurrentNodeId(int value) { currentNodeId = value; }

QList<Node *> *Map::getNodes() const { return nodes; }
QList<Link *> *Map::getLinks() const { return links; }

bool Map::getLoading() const { return loading; }
void Map::setLoading(bool value) { loading = value; }

void Map::addNode(Node *node)
{
    nodes->append(node);

    if (!loading) {
        node->setId(currentNodeId);
        currentNodeId++;
        changed = true;
    }
}

void Map::addEdge(Link *edge)
{
    links->append(edge);

    if (!loading) {
        changed = true;
    }
}

Node * Map::getNodeById(int id)
{
    for (int i = 0; i < nodes->count(); i++)
    {
        if (((Node*)nodes->value(i))->getId() == id)
            return nodes->value(i);
    }

    return 0;
}

/**
 * @brief Map::save Sauvegarde la map dans un fichier *.unmap en incluant les nodes et les liaisons
 * @param folderPath
 * @return
 */
bool Map::save(QString path)
{
    if (changed || filePath.isEmpty() || !QFile(filePath).exists())
    {
        if (filePath.isEmpty())
        {
            changed = !(UnmapManagement::saveMap(this, path));
        }
        else {
            changed = !(UnmapManagement::saveMap(this, filePath));
        }
    }
    return changed;
}
