
#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSplitter>
#include <QListWidget>
#include <QScrollArea>

#include "widgets/dragwidget.h"

#include "dialog/projectsettingsdialog.h"

#include <QGraphicsView>
#include "graphicsscene.h"

#include "core/map.h"


namespace Ui {
class MainWindow;
}
class MainWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    MainWindow(QStringList filePaths, QWidget *parent = 0);
    ~MainWindow();

    int getCurrentIndex();

    Map *getCurrentMap();
    Map *getMap(int index);
    bool hasCurrentMap();

    bool saveMap(int index);

    bool closeTab(int index);
    bool closeAllTabs();
    bool createNewTab(Map *map);

protected:
    void closeEvent(QCloseEvent *event);

private:
    Ui::MainWindow *ui;

    QTabWidget *workspaceTab;
    QListWidget * openFilesList;

    bool creationMode;

private slots:
    void enableActions();

    void on_actionNouveau_triggered();
    void on_actionOuvrir_triggered();
    void on_actionEnregistrer_triggered();
    void on_actionFermer_triggered();
    void on_actionQuitter_triggered();
    void on_actionProprietes_triggered();
    void on_actionAbout_triggered();
    void on_actionModeCreation_toggled(bool value);
    void on_actionModeLiaison_toggled(bool value);
};

#endif // MAINWINDOW_H
