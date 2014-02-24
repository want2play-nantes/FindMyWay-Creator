

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtCore/QMap>
#include <QHBoxLayout>
#include <QGraphicsView>
#include "findmywayenums.h"
#include "instruments/dragwidget.h"
#include "widgets/liste_graphe.h"

QT_BEGIN_NAMESPACE
class QAction;
class QStatusBar;
class QTabWidget;
class ToolBar;
class PaletteBar;
class ImageArea;
class QLabel;
class QUndoGroup;
class QTreeView;

QT_END_NAMESPACE

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
    void initializeToolBar();
    void initializeTabWidget();
    void initializeDragbalWidget();
    void initilizeSession();

    void initializeNewTab(const bool &isOpen = false, const QString &filePath = "");

    ImageArea* getCurrentImageArea();

    ImageArea* getImageAreaByIndex(int index);
    bool closeAllTabs();
    bool isSomethingModified();

    void updateShortcuts();

    QStatusBar *mStatusBar;
    QTabWidget *mTabWidget;
    ToolBar *mToolbar, *mDragLabel,*mSession2;
    QTreeView *mSession;
    QLayout *mlayout;
    DragWidget *drg;
    PaletteBar *mPaletteBar;
    QLabel *mSizeLabel, *mPosLabel,*mColorPreviewLabel, *mColorRGBLabel;

    QMap<InstrumentsEnum, QAction*> mInstrumentsActMap;
     QAction *mSaveAction, *mSaveAsAction, *mCloseAction,
            *mUndoAction, *mRedoAction, *mCopyAction, *mCutAction,
            *mNewAction, *mOpenAction, *mExitAction, *mPasteAction, *mZoomInAction, *mZoomOutAction;
    QMenu *mInstrumentsMenu, *mToolsMenu;
    QUndoGroup *mUndoStackGroup;
    QHBoxLayout *horizontalLayout;
    liste_graphe *treeView;
   // visu_graphe * visu;
    bool mPrevInstrumentSetted; /**< Used for magnifier */
private slots:
    void activateTab(const int &index);
    void setNewSizeToSizeLabel(const QSize &size);
    void setNewPosToPosLabel(const QPoint &pos);
    void setCurrentPipetteColor(const QColor &color);
    void clearStatusBarColor();
    void setInstrumentChecked(InstrumentsEnum instrument);
    void newAct();
    void openAct();
    void helpAct();
    void saveAct();
    void saveAsAct();
    void copyAct();
    void pasteAct();
    void cutAct();
    void settingsAct();
    void resizeImageAct();
    void resizeCanvasAct();
    void rotateLeftImageAct();
    void rotateRightImageAct();
    void zoomInAct();
    void zoomOutAct();
    void advancedZoomAct();
    void closeTabAct();
    void closeTab(int index);
    void setAllInstrumentsUnchecked(QAction *action);



    void instumentsAct(bool state);
    void enableActions(int index);
    void enableCopyCutActions(bool enable);
    void clearImageSelection();
    void restorePreviousInstrument();
    void setInstrument(InstrumentsEnum instrument);
signals:
    void sendInstrumentChecked(InstrumentsEnum);

};

#endif // MAINWINDOW_H
