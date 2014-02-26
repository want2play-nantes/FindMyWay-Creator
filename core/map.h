#ifndef MAP_H
#define MAP_H

#include <QtGui>
#include <QtXml>

class Map
{
public:
    Map(QPixmap &img, QString fileName, int ufrRef, int building, int floor, int part);
    Map(QString filePath);

    bool save(QString folderPath = "");
    bool open();

private:
    QPixmap img;
    QString fileName;
    QString filePath;

    int ufrRef, building, floor, part;

    QDomDocument *createXml();
};

#endif // MAP_H
