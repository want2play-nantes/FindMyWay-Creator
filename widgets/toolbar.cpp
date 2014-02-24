
#include "toolbar.h"
//#include "colorchooser.h"
#include "../datasingleton.h"


#include <QToolButton>
#include <QGridLayout>
#include <QSpinBox>
#include <QAction>
#include <QtCore/QMap>
#include "instruments/dragwidget.h"

ToolBar::ToolBar(const QMap<InstrumentsEnum, QAction *> &actMap, QWidget *parent) :
    QToolBar(tr("Instruments"), parent), mActMap(actMap)
{
    setMovable(true);
    initializeItems();
    mPrevInstrumentSetted = false;
}

QToolButton* ToolBar::createToolButton(QAction *act)
{
    QToolButton *toolButton = new QToolButton();
    toolButton->setMinimumSize(QSize(30, 30));
    toolButton->setMaximumSize(QSize(30, 30));
    toolButton->setDefaultAction(act);
    toolButton->setStatusTip(act->text());
    return toolButton;
}

void ToolBar::initializeItems()
{
    mCursorButton = createToolButton(mActMap[CURSOR]);
    mLineButton = createToolButton(mActMap[LINE]);
    mMagnifierButton = createToolButton(mActMap[MAGNIFIER]);
    mRectangleButton = createToolButton(mActMap[RECTANGLE]);
    mEllipseButton = createToolButton(mActMap[ELLIPSE]);



    QGridLayout *bLayout = new QGridLayout();
    bLayout->setMargin(1);
    bLayout->addWidget(mCursorButton, 1, 0);
    bLayout->addWidget(mMagnifierButton, 1, 1);
    bLayout->addWidget(mLineButton, 1, 2);
    bLayout->addWidget(mRectangleButton, 1, 3);
    bLayout->addWidget(mEllipseButton, 1, 4);



    QWidget *bWidget = new QWidget();
    bWidget->setLayout(bLayout);


    QSpinBox *penSizeSpin = new QSpinBox();
    penSizeSpin->setRange(1, 20);
    penSizeSpin->setValue(1);
    penSizeSpin->setStatusTip(tr("Pen size"));
    penSizeSpin->setToolTip(tr("Pen size"));
    connect(penSizeSpin, SIGNAL(valueChanged(int)), this, SLOT(penValueChanged(int)));

    QGridLayout *tLayout = new QGridLayout();
    tLayout->setMargin(3);
    tLayout->addWidget(penSizeSpin, 1, 0, 1, 2);
        QWidget *tWidget = new QWidget();
    tWidget->setLayout(tLayout);

    addWidget(bWidget);
    addSeparator();
    addWidget(tWidget);
}



void ToolBar::contextMenuEvent(QContextMenuEvent *)
{
}
