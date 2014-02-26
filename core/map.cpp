#include "map.h"

#include <QMessageBox>

static QString FileExt = QString("unmap");

Map::Map(QPixmap &img, QString fileName, int ufrRef, int building, int floor, int part) :
    img(img),
    fileName(fileName),
    ufrRef(ufrRef),
    building(building),
    floor(floor),
    part(part)
{

}

bool Map::save(QString folderPath)
{
    QDir dir(QString(QDir::tempPath()));
    dir.mkdir(fileName);

    QDomDocument *datas = createXml();

    QFile dataFile(QString(QDir::tempPath() + "/" + fileName + "/data.xml"));
    QFile imgFile(QString(QDir::tempPath() + "/" + fileName + "/map.png"));

    bool allFilesCreated = false;
    int result;

    if(dataFile.open(QIODevice::WriteOnly))
    {
        QTextStream ts(&dataFile);

        datas->save(ts, 4);

        dataFile.close();

        if (imgFile.open(QIODevice::WriteOnly))
        {
            img.save(&imgFile, "PNG");
            imgFile.close();

            allFilesCreated = true;
        }
        else {
            dataFile.remove();
            imgFile.remove();
        }
    }
    else {
        dataFile.remove();
    }

    // Création du fichier *.unmap
    if(allFilesCreated)
    {
        QString command("cd " + QDir::tempPath() + "/" + fileName + "; tar -zcvf "+ (!(filePath.isEmpty()) ? filePath : folderPath) + "/" + fileName + "." + FileExt + " *");
        result = system(command.toStdString().c_str());
    }

    dir.removeRecursively();

    return (result == 0);
}

bool Map::open()
{


    return false;
}

QDomDocument * Map::createXml()
{
    QDomDocument *datas = new QDomDocument(fileName);

    QDomNode xmlNode = datas->createProcessingInstruction("xml","version=\"1.0\" encoding=\"UTF-8\"");
    datas->insertBefore(xmlNode, datas->firstChild());

    QDomElement root = datas->createElement("map");
    datas->appendChild(root);

    // Properties

    QDomElement properties = datas->createElement("properties");
    root.appendChild(properties);

    QDomElement nameElement = datas->createElement("name");
    properties.appendChild(nameElement);

    QDomText nameText = datas->createTextNode(fileName);
    nameElement.appendChild(nameText);

    QDomElement ufrRefElement = datas->createElement("ufr");
    properties.appendChild(ufrRefElement);

    QDomText ufrRefText = datas->createTextNode(QString::number(ufrRef));
    ufrRefElement.appendChild(ufrRefText);

    QDomElement buildingElement = datas->createElement("building");
    properties.appendChild(buildingElement);

    QDomText buildingText = datas->createTextNode(QString::number(building));
    buildingElement.appendChild(buildingText);

    QDomElement floorElement = datas->createElement("floor");
    properties.appendChild(floorElement);

    QDomText floorText = datas->createTextNode(QString::number(floor));
    floorElement.appendChild(floorText);

    QDomElement partElement = datas->createElement("part");
    properties.appendChild(partElement);

    QDomText partText = datas->createTextNode(QString::number(part));
    partElement.appendChild(partText);

    // Graph

    QDomElement graph = datas->createElement("graph");
    root.appendChild(graph);

    // Nodes

    QDomElement nodes = datas->createElement("nodes");
    graph.appendChild(nodes);



    // Edges

    QDomElement edges = datas->createElement("edges");
    graph.appendChild(edges);



    return datas;
}

