#include "mainwindow.h"
#include "imagearea.h"
#include "ui_mainwindow.h"

#include <QApplication>
#include <QAction>
#include <QMenu>
#include <QMenuBar>
#include <QMessageBox>
#include <QScrollArea>
#include <QLabel>
#include <QtEvents>
#include <QPainter>
#include <QInputDialog>
#include <QtCore/QTimer>
#include <QtCore/QMap>
#include "widgets/dragwidget.h"
#include "dialog/projectsettingsdialog.h"


MainWindow::MainWindow(QStringList filePaths, QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // Icone de l'application
    setWindowIcon(QIcon(":/media/logo/FindMyWAy.png"));

    // Initialisation des menus
    initializeMainMenu();

    // Initialisation des tabs
    initializeTabWidget();

    // Initialisation de la liste
    initilizeSession();

    // Initialisation des zones de drag & drop
    initializeDragbalWidget();

    horizontalLayout = new QHBoxLayout;

    setCentralWidget(this->centralWidget());
}

MainWindow::~MainWindow()
{
    
}

void MainWindow::initializeTabWidget()
{
    mTabWidget = new QTabWidget(this);

    mTabWidget->setUsesScrollButtons(true);
    mTabWidget->setTabsClosable(true);

    mTabWidget->setMovable(true);
    mTabWidget->setAcceptDrops(true);

    connect(mTabWidget, SIGNAL(currentChanged(int)), this, SLOT(activateTab(int)));
    connect(mTabWidget, SIGNAL(currentChanged(int)), this, SLOT(enableActions(int)));
    connect(mTabWidget, SIGNAL(tabCloseRequested(int)), this, SLOT(closeTab(int)));

    ui->scrollArea->setWidget(mTabWidget);

}

bool MainWindow::initializeNewTab(const QString &filePath)
{
    if (filePath.isEmpty())
        return false;

    QString tabName(tr("Untitled Image"));

    ImageArea *imageArea = new ImageArea(filePath, this);
    tabName = imageArea->getFileName();

    QScrollArea * scrollArea = new QScrollArea();
    scrollArea->setAttribute(Qt::WA_DeleteOnClose);
    scrollArea->setBackgroundRole(QPalette::Dark);
    scrollArea->setWidget(imageArea);

    mTabWidget->addTab(scrollArea, tabName);
    mTabWidget->setCurrentIndex(mTabWidget->count()-1);

    setWindowTitle(QString("%1 - Find my way").arg(tabName));

    return true;
}

void MainWindow::initializeMainMenu()
{
    QMenu *fileMenu = menuBar()->addMenu(tr("&Fichier"));
    {
        mNewAction = new QAction(tr("&Nouveau..."), this);
        mNewAction->setShortcut(QKeySequence::New);
        mNewAction->setIcon(QIcon::fromTheme("document-new", QIcon(":/media/actions-icons/document-new.png")));
        mNewAction->setIconVisibleInMenu(true);
        connect(mNewAction, SIGNAL(triggered()), this, SLOT(newAct()));
        fileMenu->addAction(mNewAction);

        mOpenAction = new QAction(tr("&Ouvrir..."), this);
        mOpenAction->setShortcut(QKeySequence::Open);
        mOpenAction->setIcon(QIcon::fromTheme("document-open", QIcon(":/media/actions-icons/document-open.png")));
        mOpenAction->setIconVisibleInMenu(true);
        connect(mOpenAction, SIGNAL(triggered()), this, SLOT(openAct()));
        fileMenu->addAction(mOpenAction);

        mSaveAction = new QAction(tr("&Sauvegarder..."), this);
        mSaveAction->setShortcut(QKeySequence::Save);
        mSaveAction->setIcon(QIcon::fromTheme("document-save", QIcon(":/media/actions-icons/document-save.png")));
        mSaveAction->setIconVisibleInMenu(true);
        connect(mSaveAction, SIGNAL(triggered()), this, SLOT(saveAct()));
        fileMenu->addAction(mSaveAction);

        mSaveAsAction = new QAction(tr("Sauvegarder sous..."), this);
        mSaveAsAction->setShortcut(QKeySequence::SaveAs);
        mSaveAsAction->setIcon(QIcon::fromTheme("document-save-as", QIcon(":/media/actions-icons/document-save-as.png")));
        mSaveAsAction->setIconVisibleInMenu(true);
        connect(mSaveAsAction, SIGNAL(triggered()), this, SLOT(saveAsAct()));
        fileMenu->addAction(mSaveAsAction);

        mCloseAction = new QAction(tr("&Fermer"), this);
        mCloseAction->setShortcut(QKeySequence::Close);
        mCloseAction->setIcon(QIcon::fromTheme("window-close", QIcon(":/media/actions-icons/window-close.png")));
        mCloseAction->setIconVisibleInMenu(true);
        connect(mCloseAction, SIGNAL(triggered()), this, SLOT(closeTabAct()));
        fileMenu->addAction(mCloseAction);

        fileMenu->addSeparator();

        mPropertiesAction = new QAction(tr("&Propriétés"), this);
        mPropertiesAction->setShortcut(QKeySequence::Preferences);
        mPropertiesAction->setIcon(QIcon::fromTheme("document-properties", QIcon(":/media/actions-icons/document-properties.png")));
        mPropertiesAction->setIconVisibleInMenu(true);
        connect(mPropertiesAction, SIGNAL(triggered()), this, SLOT(settingsAct()));
        fileMenu->addAction(mPropertiesAction);

        fileMenu->addSeparator();

        mExitAction = new QAction(tr("&Quitter"), this);
        mExitAction->setShortcut(QKeySequence::Quit);
        mExitAction->setIcon(QIcon::fromTheme("application-exit", QIcon(":/media/actions-icons/application-exit.png")));
        mExitAction->setIconVisibleInMenu(true);
        connect(mExitAction, SIGNAL(triggered()), SLOT(close()));
        fileMenu->addAction(mExitAction);
    }

    QMenu *zoomMenu = menuBar()->addMenu(tr("Zoom"));
    {
        mZoomInAction = new QAction(tr("Zoom avant"), this);
        mZoomInAction->setShortcut(QKeySequence::ZoomIn);
        mZoomInAction->setIcon(QIcon::fromTheme("zoom-in", QIcon(":/media/actions-icons/zoom-in.png")));
        mZoomInAction->setIconVisibleInMenu(true);
        connect(mZoomInAction, SIGNAL(triggered()), this, SLOT(zoomInAct()));
        zoomMenu->addAction(mZoomInAction);

        mZoomOutAction = new QAction(tr("Zoom arrière"), this);
        mZoomOutAction->setShortcut(QKeySequence::ZoomOut);
        mZoomOutAction->setIcon(QIcon::fromTheme("zoom-out", QIcon(":/media/actions-icons/zoom-out.png")));
        mZoomOutAction->setIconVisibleInMenu(true);
        connect(mZoomOutAction, SIGNAL(triggered()), this, SLOT(zoomOutAct()));
        zoomMenu->addAction(mZoomOutAction);

        mAdvancedZoomAction = new QAction(tr("Zoom avancé..."), this);
        mAdvancedZoomAction->setIconVisibleInMenu(true);
        connect(mAdvancedZoomAction, SIGNAL(triggered()), this, SLOT(advancedZoomAct()));
        zoomMenu->addAction(mAdvancedZoomAction);
    }

    QMenu *aboutMenu = menuBar()->addMenu(tr("&A propos"));
    {
        mAboutAction = new QAction(tr("&About FindMyWay"), this);
        mAboutAction->setShortcut(QKeySequence::HelpContents);
        mAboutAction->setIcon(QIcon::fromTheme("help-about", QIcon(":/media/actions-icons/help-about.png")));
        mAboutAction->setIconVisibleInMenu(true);
        connect(mAboutAction, SIGNAL(triggered()), this, SLOT(helpAct()));
        aboutMenu->addAction(mAboutAction);

        mAboutQtAction = new QAction(tr("A propos de Qt"), this);
        connect(mAboutQtAction, SIGNAL(triggered()), qApp, SLOT(aboutQt()));
        aboutMenu->addAction(mAboutQtAction);
    }
}

void MainWindow::initilizeSession(){

    treeView = new ListGraph(ui->treeView);

    treeView->setObjectName(QString::fromUtf8("treeView"));
    treeView->setStyleSheet(QString::fromUtf8("border:none;"));
}

void MainWindow::initializeDragbalWidget()
{
    this->setAcceptDrops(true);
    drg1 = new DragWidget(this);
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

}

ImageArea* MainWindow::getCurrentImageArea()
{
    if (mTabWidget->currentWidget()) {
        QScrollArea *tempScrollArea = qobject_cast<QScrollArea*>(mTabWidget->currentWidget());
        ImageArea *tempArea = qobject_cast<ImageArea*>(tempScrollArea->widget());
        return tempArea;
    }
    return NULL;
}

ImageArea* MainWindow::getImageAreaByIndex(int index)
{
    QScrollArea *sa = static_cast<QScrollArea*>(mTabWidget->widget(index));
    ImageArea *ia = static_cast<ImageArea*>(sa->widget());
    return ia;
}

void MainWindow::activateTab(const int &index)
{
    if(index == -1)
        return;

    mTabWidget->setCurrentIndex(index);

    if(!getCurrentImageArea()->getFileName().isEmpty())
    {
        setWindowTitle(QString("%1 - FindMyWay").arg(getCurrentImageArea()->getFileName()));
    }
    else
    {
        setWindowTitle(QString("%1 - FindMyWay").arg(tr("Untitled Image")));
    }
}

void MainWindow::setNewSizeToSizeLabel(const QSize &size)
{
    mSizeLabel->setText(QString("%1 x %2").arg(size.width()).arg(size.height()));
}

void MainWindow::setNewPosToPosLabel(const QPoint &pos)
{
    mPosLabel->setText(QString("%1,%2").arg(pos.x()).arg(pos.y()));
}

void MainWindow::setCurrentPipetteColor(const QColor &color)
{
    mColorRGBLabel->setText(QString("RGB: %1,%2,%3").arg(color.red())
                            .arg(color.green()).arg(color.blue()));

    QPixmap statusColorPixmap = QPixmap(10, 10);
    QPainter statusColorPainter;
    statusColorPainter.begin(&statusColorPixmap);
    statusColorPainter.fillRect(0, 0, 15, 15, color);
    statusColorPainter.end();
    mColorPreviewLabel->setPixmap(statusColorPixmap);
}

void MainWindow::newAct()
{
    /*
     * Lancement de la fenêtre Nouveau projet
     * Création d'un objet Map
     * Ouverture d'un nouvel onglet + zone de travail
     * Affichage de l'image
     */

    ProjectSettingsDialog projectSettingsDialog(this);

    if (projectSettingsDialog.exec() == QDialog::Accepted)
    {
        if (initializeNewTab(projectSettingsDialog.getMapPath()))
        {
            treeView->nouveau_liste_item(getCurrentImageArea()->getFileName());
        }

        //mTabWidget->setTabText(mTabWidget->currentIndex(), getCurrentImageArea()->getFileName().isEmpty() ? tr("Untitled Image") : getCurrentImageArea()->getFileName() );

        //QMessageBox msgBox;
        //msgBox.setText("Création d'un nouveau fichier avec les informations entrées.");
        //msgBox.exec();
    }
}

void MainWindow::openAct()
{
    /*
     * Chargement de l'objet Map
     */

    //initializeNewTab(true);
}

void MainWindow::saveAct()
{
    getCurrentImageArea()->save();
    mTabWidget->setTabText(mTabWidget->currentIndex(), getCurrentImageArea()->getFileName().isEmpty() ? tr("Untitled Image") : getCurrentImageArea()->getFileName() );
    treeView->nouveau_liste_item(getCurrentImageArea()->getFileName());

}

void MainWindow::saveAsAct()
{
    getCurrentImageArea()->saveAs();
    mTabWidget->setTabText(mTabWidget->currentIndex(), getCurrentImageArea()->getFileName().isEmpty() ? tr("Untitled Image") : getCurrentImageArea()->getFileName() );
}

void MainWindow::settingsAct()
{
    /*
     * Ouvre un ProjectSettingsDialog en mode édition
     */

    //MapPropertiesDialog settingsDialog(this);
    //if(settingsDialog.exec() == QDialog::Accepted)
    //{
    //    mTabWidget->setTabText(mTabWidget->currentIndex(), getCurrentImageArea()->getFileName().isEmpty() ? tr("Untitled Image") : getCurrentImageArea()->getFileName() );
    //}
}

void MainWindow::zoomInAct()
{
    getCurrentImageArea()->zoomImage(2.0);
    getCurrentImageArea()->setZoomFactor(2.0);
}

void MainWindow::zoomOutAct()
{
    getCurrentImageArea()->zoomImage(0.5);
    getCurrentImageArea()->setZoomFactor(0.5);
}

void MainWindow::advancedZoomAct()
{
    bool ok;
    qreal factor = QInputDialog::getDouble(this, tr("Enter zoom factor"), tr("Zoom factor:"), 2.5, 0, 1000, 5, &ok);
    if (ok)
    {
        getCurrentImageArea()->zoomImage(factor);
        getCurrentImageArea()->setZoomFactor(factor);
    }
}

void MainWindow::closeTabAct()
{
    closeTab(mTabWidget->currentIndex());
}

void MainWindow::closeTab(int index)
{
    ImageArea *ia = getImageAreaByIndex(index);
    if(ia->getEdited())
    {
        int ans = QMessageBox::warning(this, tr("Closing Tab..."),
                                       tr("File has been modified.\nDo you want to save changes?"),
                                       QMessageBox::Yes | QMessageBox::Default,
                                       QMessageBox::No, QMessageBox::Cancel | QMessageBox::Escape);
        switch(ans)
        {
        case QMessageBox::Yes:
            if (ia->save())
                break;
            return;
        case QMessageBox::Cancel:
            return;
        }
    }

    QWidget *wid = mTabWidget->widget(index);
    mTabWidget->removeTab(index);

    delete wid;

    if (mTabWidget->count() == 0)
    {
        setWindowTitle("Empty - Find my way");
    }
}

void MainWindow::closeEvent(QCloseEvent *event)
{
    if(!isSomethingModified() || closeAllTabs())
    {
        event->accept();
    }
    else
        event->ignore();
}

bool MainWindow::isSomethingModified()
{
    for(int i = 0; i < mTabWidget->count(); ++i)
    {
        if(getImageAreaByIndex(i)->getEdited())
            return true;
    }
    return false;
}

bool MainWindow::closeAllTabs()
{

    while(mTabWidget->count() != 0)
    {
        ImageArea *ia = getImageAreaByIndex(0);
        if(ia->getEdited())
        {
            int ans = QMessageBox::warning(this, tr("Closing Tab..."),
                                           tr("File has been modified.\nDo you want to save changes?"),
                                           QMessageBox::Yes | QMessageBox::Default,
                                           QMessageBox::No, QMessageBox::Cancel | QMessageBox::Escape);
            switch(ans)
            {
            case QMessageBox::Yes:
                if (ia->save())
                    break;
                return false;
            case QMessageBox::Cancel:
                return false;
            }
        }
        QWidget *wid = mTabWidget->widget(0);
        mTabWidget->removeTab(0);
        delete wid;
    }
    return true;
}

void MainWindow::enableActions(int index)
{
    //if index == -1 it means, that there is no tabs
    bool isEnable = index == -1 ? false : true;

    mSaveAction->setEnabled(isEnable);
    mSaveAsAction->setEnabled(isEnable);
    mCloseAction->setEnabled(isEnable);
}

void MainWindow::helpAct()
{
    QMessageBox::about(this, tr("About Find My Way"),
                       QString("Project IHM M1 ALMA")
                       .arg(tr("version")).arg("0.1.0").arg(tr("Site")).arg(tr("Authors"))
                       .arg(tr("If you like <b>FindMyWay</b> and you want to share your opinion, or send a bug report, or want to suggest new features, we are waiting for you on our <a>arafet.ferdjani@gmail.com</a>.")));
}
