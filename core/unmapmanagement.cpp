#include "unmapmanagement.h"

#include "core/nodes/classroom.h"

static QString UNMAP_EXTENSION = QString("unmap");
//static QString UNMAP_EXTENSION = QString("tar.gz");

static QString DATA_FILE = QString("data.xml");
static QString IMG_FILE = QString("map.png");

// Tag du fichier de données XML
static QString XML_ROOT_TAG = QString("map");
static QString XML_NAME_ATT = QString("name");
static QString XML_UFR_ATT = QString("ufr");
static QString XML_BUILDING_ATT = QString("building");
static QString XML_FLOOR_ATT = QString("floor");
static QString XML_PART_ATT = QString("part");
static QString XML_CURRENT_ID_ATT = QString("current-id");

static QString XML_GRAPH_TAG = QString("graph");
static QString XML_NODES_TAG = QString("nodes");
static QString XML_LINKS_TAG = QString("links");

static QString XML_NODE_TAG = QString("node");
    static QString XML_ID_ATT = QString("id");
    static QString XML_TYPE_ATT = QString("type");
    static QString XML_X_ATT = QString("x");
    static QString XML_Y_ATT = QString("y");

static QString XML_LINK_TAG = QString("link");
    static QString XML_FROM_ATT = QString("from");
    static QString XML_TO_ATT = QString("to");
    static QString XML_DISTANCE_ATT = QString("distance");
    static QString XML_MAP_ATT = QString("map");

UnmapManagement::UnmapManagement()
{
}

/**
 * @brief UnmapManagement::saveMap Sauvegarder une carte dans un fichier
 * @param map carte
 * @param path chemin du fichier
 */
bool UnmapManagement::saveMap(Map *map, QString path)
{
    // Création du dossier temporaire
    QDir dir(QString(QDir::tempPath()));
    dir.mkdir(map->getFileName());

    // Création du fichier XML
    QDomDocument *datas = createXml(map);

    // Définition des fichiers de données et de l'image
    QFile dataFile(QString(QDir::tempPath() + "/" + map->getFileName() + "/" + DATA_FILE));
    QFile imgFile(QString(QDir::tempPath() + "/" + map->getFileName() + "/" + IMG_FILE));

    bool allFilesCreated = false;
    int result;

    // Ouverture du fichier de données
    if(dataFile.open(QIODevice::WriteOnly))
    {
        QTextStream ts(&dataFile);

        // Ecriture des données dans le fichier de données
        datas->save(ts, 4);

        dataFile.close();

        // Ouverture du fichier image
        if (imgFile.open(QIODevice::WriteOnly))
        {
            // Ecriture de l'image dans le fichier image
            map->getImg()->save(&imgFile, "PNG");
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
        if (map->getFilePath().isEmpty())
            map->setFilePath(QString(path + "/" + map->getFileName() + "." + UNMAP_EXTENSION));

        QString command("cd " + QDir::tempPath() + "/" + map->getFileName() + "; tar -zcvf " + map->getFilePath() + " *");
        result = system(command.toStdString().c_str());
    }

    // Suppression du dossier et des fichiers temporaires
    dir.removeRecursively();

    return (result == 0);
}

/**
 * @brief UnmapManagement::openMap
 * @param map
 */
Map* UnmapManagement::openMap(QString path)
{
    Map *map;

    QString command("tar -zxvf " + path + " -C " + QDir::tempPath() + "/");
    system(command.toStdString().c_str());

    QFile dataFile(QString(QDir::tempPath() + "/" + DATA_FILE));

    QDomDocument datas;

    if (dataFile.open(QIODevice::ReadOnly))
    {
        datas.setContent(&dataFile);
        dataFile.close();
    }

    map = loadXml(&datas);

    QPixmap *img = new QPixmap(QDir::tempPath() + "/" + IMG_FILE);
    map->setImg(img);

    map->setFilePath(path);
    map->setChanged(false);

    return map;
}

/**
 * @brief UnmapManagement::loadXml
 * @param datas
 */
Map *UnmapManagement::loadXml(QDomDocument * datas)
{
    QString fileName;
    int ufrRef, building, floor, part;
    int currentNodeId;

    QDomElement root = datas->documentElement();

    fileName = root.attribute(XML_NAME_ATT);
    ufrRef = root.attribute(XML_UFR_ATT).toInt();
    building = root.attribute(XML_BUILDING_ATT).toInt();
    floor = root.attribute(XML_FLOOR_ATT).toInt();
    part = root.attribute(XML_PART_ATT).toInt();

    Map * map = new Map(NULL, fileName, ufrRef, building, floor, part);

    currentNodeId = root.attribute(XML_CURRENT_ID_ATT).toInt();
    map->setCurrentNodeId(currentNodeId);

    map->setLoading(true);

    // Lecture du graph
    QDomNode graph = root.firstChild();

    QDomElement e;

    // Lecture des noeuds
    QDomNode nodes = graph.firstChild();

    int id, type, x, y;

    e = nodes.firstChildElement();

    while(!e.isNull())
    {
        x = e.attribute(XML_X_ATT).toInt();
        y = e.attribute(XML_Y_ATT).toInt();
        id = e.attribute(XML_ID_ATT).toInt();
        type = e.attribute(XML_TYPE_ATT).toInt();

        Node *n = NULL;

        switch (type)
        {
        case 0:     n = new Classroom(map, x, y); n->setId(id); qDebug() << "Création Classroom : id =" << id; break;
        default:    break;
        }

        e = e.nextSibling().toElement();
    }

    // Lecture des liaisons
    QDomNode links = nodes.nextSibling();

    int to, from, distance;
    QString mapName;

    e = links.firstChildElement();

    while(!e.isNull())
    {
        to = e.attribute(XML_TO_ATT).toInt();
        from = e.attribute(XML_FROM_ATT).toInt();
        distance = e.attribute(XML_DISTANCE_ATT).toInt();

        mapName = e.attribute(XML_MAP_ATT);
        // TODO : Charger une carte distante -> Proxy !

        new Link(map, map->getNodeById(from), map->getNodeById(to), distance);
        qDebug() << "Création Link :" << map->getNodeById(from)->getId() << "->" << map->getNodeById(to)->getId() << "(" << distance << ")";

        e = e.nextSibling().toElement();
    }

    map->setLoading(false);

    return map;
}

/**
 * @brief UnmapManagement::createXml
 * @param map
 * @return
 */
QDomDocument * UnmapManagement::createXml(Map *map)
{
    QDomDocument *datas = new QDomDocument();

    QDomNode xmlNode = datas->createProcessingInstruction("xml","version=\"1.0\" encoding=\"UTF-8\"");
    datas->insertBefore(xmlNode, datas->firstChild());

    QDomElement root = datas->createElement(XML_ROOT_TAG);

    root.setAttribute(XML_NAME_ATT, map->getFileName());
    root.setAttribute(XML_UFR_ATT, map->getUfrRef());
    root.setAttribute(XML_BUILDING_ATT, map->getBuilding());
    root.setAttribute(XML_FLOOR_ATT, map->getFloor());
    root.setAttribute(XML_PART_ATT, map->getPart());
    root.setAttribute(XML_CURRENT_ID_ATT, map->getCurrentNodeId());

    datas->appendChild(root);

    // Graph

    QDomNode graph = datas->createElement(XML_GRAPH_TAG);
    root.appendChild(graph);

    // Nodes

    // TODO : cree l'arbre DOM dans la classe Node

    QDomNode nodes = datas->createElement(XML_NODES_TAG);

    for (int index = 0; index < map->getNodes()->count(); index++)
    {
        Node *node = map->getNodes()->value(index);

        QDomElement nodeElement = datas->createElement(XML_NODE_TAG);

        nodeElement.setAttribute(XML_ID_ATT, node->getId());
        nodeElement.setAttribute(XML_TYPE_ATT, node->getType());
        nodeElement.setAttribute(XML_X_ATT, node->getX());
        nodeElement.setAttribute(XML_Y_ATT, node->getY());

        nodes.appendChild(nodeElement);
    }

    graph.appendChild(nodes);

    // Links

    // TODO : cree l'arbre DOM dans la classe Link

    QDomElement links = datas->createElement(XML_LINKS_TAG);

    for (int index = 0; index < map->getLinks()->count(); index++)
    {
        Link *link = map->getLinks()->value(index);

        QDomElement linkElement = datas->createElement(XML_LINK_TAG);

        linkElement.setAttribute(XML_FROM_ATT, link->getFrom()->getId());
        linkElement.setAttribute(XML_TO_ATT, link->getTo()->getId());
        linkElement.setAttribute(XML_DISTANCE_ATT, link->getDistance());

        if ((link->getTo()->getMap() != 0) && (map->getFileName() != link->getTo()->getMap()->getFileName()))
        {
            linkElement.setAttribute(XML_MAP_ATT, link->getMap()->getFileName());
        }

        // TODO : A tester avec un noeud distance => la carte peut ne pas être chargée

        links.appendChild(linkElement);
    }

    graph.appendChild(links);

    return datas;
}
