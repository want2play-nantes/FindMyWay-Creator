#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "core/unmapmanagement.h"
#include "core/nodes/classroom.h"

MainWindow::MainWindow(QStringList filePaths, QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow), creationMode(true)
{
    ui->setupUi(this);

    openFilesList = new QListWidget();
    openFilesList->setSortingEnabled(true);

    QTabWidget *leftTabWidget;
    QTabWidget *rightTabWidget;

    QScrollArea *scrollArea;
    QSplitter *splitter;

    splitter= new QSplitter(this);
    ui->horizontalLayout->addWidget(splitter);

    leftTabWidget = new QTabWidget;
    leftTabWidget->setMaximumWidth(250);
    leftTabWidget->addTab(openFilesList, QIcon(), "Fichiers ouverts");
    splitter->addWidget(leftTabWidget);

    workspaceTab = new QTabWidget;
    workspaceTab->setTabsClosable(true);
    workspaceTab->setMovable(true);
    splitter->addWidget(workspaceTab);

    scrollArea = new QScrollArea;
    scrollArea->setWidget(new DragWidget(this));
    rightTabWidget = new QTabWidget;
    rightTabWidget->setMinimumWidth(200);
    rightTabWidget->setMaximumWidth(200);
    rightTabWidget->addTab(scrollArea, QIcon(), "Elements");

    ui->horizontalLayout->addWidget(rightTabWidget);

    enableActions();
}

MainWindow::~MainWindow()
{
    
}

bool MainWindow::createNewTab(Map *map)
{
    GraphicsScene *gs = new GraphicsScene(map);
    QGraphicsView *gv = new QGraphicsView(gs);

    gv->setDragMode(QGraphicsView::RubberBandDrag);
    gv->setStyleSheet("background-color:#999");
    gv->setRenderHint(QPainter::Antialiasing);
    gv->setCacheMode(QGraphicsView::CacheBackground);

<<<<<<< HEAD
    workspaceTab->addTab(gv, QIcon(), map->getFileName());
    workspaceTab->setCurrentIndex(workspaceTab->count()-1);
=======
    tabWidget1->addTab(treeView,QIcon("://media/instruments-icons/rectangle.png"),"Projects");

    QString str("10_14_01.png");
    treeView->addItem(str);
    splitter->addWidget(tabWidget1);

    layout->addWidget(splitter,2);

    tabWidget2->addTab(gr,QIcon("://media/instruments-icons/rectangle.png"),"Works area");

    splitter2->addWidget(tabWidget2);

    layout->addWidget(splitter2,8);



    tabWidget3->addTab(scrollArea,QIcon("://media/instruments-icons/rectangle.png"),"Drag&drop");
    layout->addWidget(tabWidget3,2);
    setCentralWidget(widget);
>>>>>>> 2397366b5e787a1dca2335a554b8d551d6846085

    QListWidgetItem *item = new QListWidgetItem(map->getFileName());
    openFilesList->addItem(item);

    return true;
}

int MainWindow::getCurrentIndex()
{
<<<<<<< HEAD
    return workspaceTab->currentIndex();
}
=======
    /*
    if (filePath.isEmpty())
        return false;

    QString tabName(tr("Untitled Image"));

    ImageArea *imageArea = new ImageArea(filePath, this);
    tabName = imageArea->getFileName();
   // sc = new Graphicscene(filePath);


    QScrollArea * scrollArea = new QScrollArea();
    scrollArea->setAttribute(Qt::WA_DeleteOnClose);
    scrollArea->setBackgroundRole(QPalette::Dark);
    scrollArea->setWidget(imageArea);
   // treeView->nouveau_liste_item(filePath);
    mTabWidget->addTab(scrollArea, filePath);
    mTabWidget->setCurrentIndex(mTabWidget->count()-1);
    /*QGraphicsView *qw = new QGraphicsView(this);
    qw->setScene(sc);


>>>>>>> 2397366b5e787a1dca2335a554b8d551d6846085

bool MainWindow::hasCurrentMap()
{
    return getCurrentIndex() != -1;
}

<<<<<<< HEAD
Map* MainWindow::getCurrentMap()
{
    return getMap(getCurrentIndex());
}

Map* MainWindow::getMap(int index)
{
    QGraphicsView * gv = (QGraphicsView*)workspaceTab->widget(index);
    GraphicsScene * gs = (GraphicsScene*)gv->scene();

    return gs->getMap();
=======
    //treeView->nouveau_liste_item(tabName);

    return true;
*/
>>>>>>> 2397366b5e787a1dca2335a554b8d551d6846085
}

bool MainWindow::closeTab(int index)
{
    Map * map = getCurrentMap();

    if (map->getChanged())
    {
        QMessageBox msgBox;
        msgBox.setText("Le document a été modifié.");
        msgBox.setInformativeText("Voulez-vous enregistrer les changements ?");
        msgBox.setStandardButtons(QMessageBox::Save | QMessageBox::Discard | QMessageBox::Cancel);
        msgBox.setDefaultButton(QMessageBox::Save);
        int ret = msgBox.exec();

        switch (ret) {
        case QMessageBox::Save:
            saveMap(index);
            return true;
            break;

        case QMessageBox::Cancel:
            return false;

        default:
            break;
        }
    }

    workspaceTab->removeTab(index);


    // TODO : Doit être améliorer (peut supprimer 2 fichiers de la liste en même temps)

<<<<<<< HEAD
    bool foundItem = false;
    int i = 0;
=======
    //this->setAcceptDrops(true);
    drg1 = new DragWidget(this);
    scrollArea->setWidget(drg1);

/*
    drg2 = new DragWidget(this);
    drg3 = new DragWidget(this);
    drg4 = new DragWidget(this);
    drg5 = new DragWidget(this);

    QLabel *boatIcon = new QLabel(this);
    boatIcon->setPixmap(QPixmap(":/logos/logos/salle.png"));
    boatIcon->move(0, 50);
    boatIcon->show();
    boatIcon->setAttribute(Qt::WA_DeleteOnClose);

    QLabel *boatIcontext = new QLabel(this);
    boatIcontext->show();
    boatIcontext->move(0, 50);
    boatIcontext->setText("salle");

    QLabel *carIcon = new QLabel(this);
    carIcon->setPixmap(QPixmap(":/logos/logos/salle.png"));
    carIcon->move(0, 60);
    carIcon->show();
    carIcon->setAttribute(Qt::WA_DeleteOnClose);


    QLabel *boatIcontext2 = new QLabel(this);
    boatIcontext2->show();
    boatIcontext2->move(0, 50);
    boatIcontext2->setText("escalier");

    QLabel *houseIcon = new QLabel(this);
    houseIcon->setPixmap(QPixmap(":/logos/logos/salle.png"));
    houseIcon->move(0, 150);
    houseIcon->show();
    houseIcon->setAttribute(Qt::WA_DeleteOnClose);

    QLabel *boatIcontext3 = new QLabel(this);
    boatIcontext3->show();
    boatIcontext3->move(0, 150);
    boatIcontext3->setText("porte");

    QLabel *houseIcon2 = new QLabel(this);
    houseIcon2->setPixmap(QPixmap(":/logos/logos/salle.png"));
    houseIcon2->move(0, 200);
    houseIcon2->show();
    houseIcon2->setAttribute(Qt::WA_DeleteOnClose);

    QLabel *boatIcontext4 = new QLabel(this);
    boatIcontext4->show();
    boatIcontext4->move(0, 200);
    boatIcontext4->setText("fenetre");

    QLabel *houseIcon3 = new QLabel(this);
    houseIcon3->setPixmap(QPixmap(":/logos/logos/salle.png"));
    houseIcon3->move(0, 200);
    houseIcon3->show();
    houseIcon3->setAttribute(Qt::WA_DeleteOnClose);

    QLabel *boatIcontext5 = new QLabel(this);
    boatIcontext5->show();
    boatIcontext5->move(0, 200);
    boatIcontext5->setText("porte principale");

    drg1->addWidget(boatIcon);
    drg1->addWidget(boatIcontext);
    ui->verticalLayout1->addWidget(drg1);
    drg2->addWidget(carIcon);
    drg2->addWidget(boatIcontext2);
    ui->verticalLayout_2->addWidget(drg2);
    drg3->addWidget(houseIcon);
    drg3->addWidget(boatIcontext3);
    ui->verticalLayout_3->addWidget(drg3);
    drg4->addWidget(houseIcon2);
    drg4->addWidget(boatIcontext4);
    ui->verticalLayout_4->addWidget(drg4);
    drg5->addWidget(houseIcon3);
    drg5->addWidget(boatIcontext5);
    ui->verticalLayout_5->addWidget(drg5);

    // ui->verticalLayout->addWidget(drg);
    // addToolBar(Qt::RightToolBarArea, drg);
*/
}
>>>>>>> 2397366b5e787a1dca2335a554b8d551d6846085

    while (i < openFilesList->count() || !foundItem)
    {
        if (openFilesList->item(i)->text() == map->getFileName())
        {
            QListWidgetItem *item = openFilesList->takeItem(i);
            delete item;
            foundItem = true;
        }
        i++;
    }

    return true;
}

bool MainWindow::closeAllTabs()
{
    for (int i = 0; i < workspaceTab->count(); i++)
    {
        if (!closeTab(i))
            return false;
    }

    return true;
}

void MainWindow::enableActions()
{
    bool isEnable = (getCurrentIndex() != -1);

    ui->actionEnregistrer->setEnabled(isEnable);
    ui->actionFermer->setEnabled(isEnable);
    ui->actionProprietes->setEnabled(isEnable);
}

void MainWindow::on_actionNouveau_triggered()
{
    ProjectSettingsDialog psd(this);

    if (psd.exec() == QDialog::Accepted)
    {
        QPixmap *img = new QPixmap(psd.getMapPath());
        Map *m = new Map(img, psd.getFileName(), psd.getUfrRef(), psd.getBuilding(), psd.getFloor(), psd.getPart());

        /*
         * Test
         */

        // Création des noeuds
        Node * n1 = new Classroom(m, 20, 20);
        Node * n2 = new Classroom(m, 40, 25);
        Node * n3 = new Classroom(m, 25, 17);
        Node * n4 = new Classroom(m, 5, 2);

        // Liaisons des noeuds
        n1->link(n2, 5);
        n1->link(n3, 7);
        n2->link(n3, 8);
        n2->link(n4, 11);
        n3->link(n4, 5);
        n1->link(n4, 18);

        /*
         * Fin test
         */

        createNewTab(m);
    }
    enableActions();
}

void MainWindow::on_actionOuvrir_triggered()
{
    QFileDialog dialog(this, tr("Ouvrir"), QDir::home().absolutePath(),tr("Fichier Unmap (*.unmap)"));
    dialog.setFileMode(QFileDialog::ExistingFile);

    if (dialog.exec())
    {
        QStringList selectedFiles = dialog.selectedFiles();
        if (!selectedFiles.isEmpty())
        {
            Map *map = UnmapManagement::openMap(selectedFiles.takeFirst());
            createNewTab(map);
        }
        enableActions();
    }
}

void MainWindow::on_actionEnregistrer_triggered()
{
    saveMap(getCurrentIndex());
}

void MainWindow::on_actionFermer_triggered()
{
    closeTab(getCurrentIndex());

    enableActions();
}

void MainWindow::on_actionQuitter_triggered()
{
    close();
}

void MainWindow::on_actionProprietes_triggered()
{
    ProjectSettingsDialog psd(this);
    psd.setEditable(getCurrentMap());
    psd.exec();
}

void MainWindow::on_actionAbout_triggered()
{
    QMessageBox::about(this, tr("À propos de FindMyWay - Creator"), QString("Application développé lors d'un projet d'Interface Homme-Machine de M1 ALMA à l'université de Nantes"));
}

void MainWindow::closeEvent(QCloseEvent *event)
{
    if(closeAllTabs())
    {
        event->accept();
    }
    else
        event->ignore();
}

bool MainWindow::saveMap(int index)
{
    Map * map = getMap(index);

    if (!map->getChanged())
        return true;

    if (map->getFilePath().isEmpty()) {
        QFileDialog dialog(this, tr("Enregistrer"), QDir::home().absolutePath());
        dialog.setFileMode(QFileDialog::Directory);
        dialog.setOption(QFileDialog::ShowDirsOnly);

        if (dialog.exec()) {
            QStringList selectedFiles = dialog.selectedFiles();
            if (!selectedFiles.isEmpty())
            {
                return map->save(selectedFiles.takeFirst());
            }
        }
    }
    else {
        return map->save();
    }

    return false;
}

void MainWindow::on_actionModeCreation_toggled(bool value)
{
    ui->actionModeLiaison->setChecked(!ui->actionModeCreation->isChecked());
    creationMode = true;
}

void MainWindow::on_actionModeLiaison_toggled(bool value)
{
    ui->actionModeCreation->setChecked(!ui->actionModeLiaison->isChecked());
    creationMode = false;
}
