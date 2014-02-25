

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtCore/QMap>
#include <QHBoxLayout>
#include <QGraphicsView>
#include "instruments/dragwidget.h"
#include "widgets/listgraph.h"

QT_BEGIN_NAMESPACE
class QAction;
class QStatusBar;
class QTabWidget;
class ImageArea;
class QLabel;
class QTreeView;

QT_END_NAMESPACE
namespace Ui {
class MainWindow;
}
class MainWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    MainWindow(QStringList filePaths, QWidget *parent = 0);
    ~MainWindow();

protected:
    void closeEvent(QCloseEvent *event);

private:
    void initializeMainMenu();
    void initializeStatusBar();
    void initializeTabWidget();
    void initializeDragbalWidget();
    void initilizeSession();

    void initializeNewTab(const bool &isOpen = false, const QString &filePath = "");

    Ui::MainWindow *ui;

    ImageArea* getCurrentImageArea();
    ImageArea* getImageAreaByIndex(int index);

    bool closeAllTabs();
    bool isSomethingModified();

    QStatusBar *mStatusBar;
    QTabWidget *mTabWidget;
    QTreeView *mSession;
    QLayout *mlayout,*mprincipale;
    DragWidget *drg1,*drg2,*drg3,*drg4,*drg5;
    QLabel *mSizeLabel, *mPosLabel,*mColorPreviewLabel, *mColorRGBLabel;

    QAction *mNewAction, *mOpenAction, *mSaveAction, *mSaveAsAction, *mCloseAction, *mExitAction, *mZoomInAction, *mZoomOutAction, *mAdvancedZoomAction, *mPropertiesAction, *mAboutAction, *mAboutQtAction;

    QMenu *mToolsMenu;

    QHBoxLayout *horizontalLayout;

    ListGraph *treeView;

private slots:
    void activateTab(const int &index);
    void setNewSizeToSizeLabel(const QSize &size);
    void setNewPosToPosLabel(const QPoint &pos);
    void setCurrentPipetteColor(const QColor &color);
    void newAct();
    void openAct();
    void helpAct();
    void saveAct();
    void saveAsAct();
    void settingsAct();
    void zoomInAct();
    void zoomOutAct();
    void advancedZoomAct();
    void closeTabAct();
    void closeTab(int index);

    void enableActions(int index);

};

#endif // MAINWINDOW_H
