

#ifndef ABSTRACTSELECTION_H
#define ABSTRACTSELECTION_H

#include "abstractinstrument.h"

QT_BEGIN_NAMESPACE
class QUndoStack;
class ImageArea;
QT_END_NAMESPACE

class AbstractSelection : public AbstractInstrument
{
    Q_OBJECT

public:
    explicit AbstractSelection(QObject *parent = 0);

    void mousePressEvent(QMouseEvent *event, ImageArea &imageArea);
    void mouseMoveEvent(QMouseEvent *event, ImageArea &imageArea);
    void mouseReleaseEvent(QMouseEvent *event, ImageArea &imageArea);

    /**
     * @brief Removes selection borders from image and clears all selection varaibles to default.
     *
     * @param imageArea ImageArea for applying changes.
     */
    void clearSelection(ImageArea &imageArea);
    /**
     * @brief Save all image changes to image copy.
     *
     */
    void saveImageChanges(ImageArea &);

    virtual void startSelection(ImageArea &imageArea) = 0;
    virtual void startResizing(ImageArea &imageArea) = 0;
    virtual void startMoving(ImageArea &imageArea) = 0;
    virtual void startAdjusting(ImageArea &imageArea) = 0;
    virtual void select(ImageArea &imageArea) = 0;
    virtual void resize(ImageArea &imageArea) = 0;
    virtual void move(ImageArea &imageArea) = 0;
    virtual void completeSelection(ImageArea &imageArea) = 0;
    virtual void completeResizing(ImageArea &imageArea) = 0;
    virtual void completeMoving(ImageArea &imageArea) = 0;
    virtual void clear() = 0;
    virtual void showMenu(ImageArea &imageArea) = 0;

protected:
    void drawBorder(ImageArea &imageArea);
    void updateCursor(QMouseEvent *event, ImageArea &imageArea);

    QPoint mBottomRightPoint, mTopLeftPoint, mMoveDiffPoint;
    bool mIsPaint, mIsSelectionExists, mIsSelectionMoving, mIsSelectionResizing, mIsImageSelected,
         mIsMouseMoved, mIsSelectionAdjusting;;
    int mHeight, mWidth;
    Qt::MouseButton mButton;
};

#endif // ABSTRACTSELECTION_H
