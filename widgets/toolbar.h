
#ifndef TOOLBAR_H
#define TOOLBAR_H

#include "../findmywayenums.h"

#include <QToolBar>
#include <QHBoxLayout>

QT_BEGIN_NAMESPACE
class QToolButton;
class ColorChooser;
QT_END_NAMESPACE

/**
 * @brief Toolbar with instrumets buttons, color choosers and etc.
 *
 */
class ToolBar : public QToolBar
{
    Q_OBJECT

public:
    explicit ToolBar(const QMap<InstrumentsEnum, QAction*> &actMap, QWidget *parent = 0);

private:
    /**
     * @brief Initialize all buttons, color choosers and etc.
     *
     */
    void initializeItems();
    /**
     * @brief Create new QToolButton
     *
     * @param name Name of button
     * @param iconPath Path to button icon.
     * @return QToolButton Created QToolButton.
     */
    QToolButton* createToolButton(QAction *act);

    QToolButton *mCursorButton, *mLineButton,
                 *mMagnifierButton, *mSprayButton, *mFillButton,
                *mRectangleButton, *mEllipseButton,*mNewButton;
    ColorChooser *mPColorChooser, *mSColorChooser;
        QHBoxLayout *horizontalLayout ;
    bool mPrevInstrumentSetted;
    const QMap<InstrumentsEnum, QAction*> &mActMap;
    
signals:
    void sendClearStatusBarColor();
    void sendClearImageSelection();

    
protected:
    void contextMenuEvent(QContextMenuEvent *);
    
};

#endif // TOOLBAR_H
