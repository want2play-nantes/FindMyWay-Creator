#ifndef MAP_H
#define MAP_H

#include <QtGui>

#include "map.h"
#include "node.h"
#include "link.h"

class Map
{
public:
    Map(QPixmap *img, QString fileName, int ufrRef, int building, int floor, int part);

    bool save(QString path = "");

    QPixmap *getImg() const;
    void setImg(QPixmap *value);

    QString getFileName() const;
    void setFileName(const QString &value);

    QString getFilePath() const;
    void setFilePath(QString value);

    int getUfrRef() const;
    void setUfrRef(int value);

    int getBuilding() const;
    void setBuilding(int value);

    int getFloor() const;
    void setFloor(int value);

    int getPart() const;
    void setPart(int value);

    bool getChanged() const;
    void setChanged(bool value);

    int getCurrentNodeId() const;
    void setCurrentNodeId(int value);

    void addNode(Node *node);
    void addEdge(Link *edge);

    QList<Node *> *getNodes() const;
    QList<Link *> *getLinks() const;

    bool getLoading() const;
    void setLoading(bool value);

    Node *getNodeById(int id);

private:
    QList<Node *> *nodes;
    QList<Link *> *links;

    QPixmap *img;

    QString fileName;
    QString filePath;

    int ufrRef;
    int building;
    int floor;
    int part;
    int currentNodeId;

    bool changed;
    bool loading;
};

#endif // MAP_H
