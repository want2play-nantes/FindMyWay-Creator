
#ifndef ABSTRACTINSTRUMENT_H
#define ABSTRACTINSTRUMENT_H

#include <QtCore/QObject>
#include <QMouseEvent>
#include <QImage>

QT_BEGIN_NAMESPACE
class ImageArea;
QT_END_NAMESPACE

/**
 * @brief Abstract instrument class.
 *
 */
class AbstractInstrument : public QObject
{
    Q_OBJECT

public:
    explicit AbstractInstrument(QObject *parent = 0);
    virtual ~AbstractInstrument(){}

    virtual void mousePressEvent(QMouseEvent *event, ImageArea &imageArea) = 0;
    virtual void mouseMoveEvent(QMouseEvent *event, ImageArea &imageArea) = 0;
    virtual void mouseReleaseEvent(QMouseEvent *event, ImageArea &imageArea) = 0;
    
signals:
    
protected:
    QPoint mStartPoint, mEndPoint; /**< Point for events. */
    QImage mImageCopy; /**< Image for storing copy of current image on imageArea, needed for some instruments. */

    virtual void paint(ImageArea &imageArea, bool isSecondaryColor = false, bool additionalFlag = false) = 0;

    /**
     * @brief Creates UndoCommand & pushes it to UndoStack.
     *
     * Base realisation simply save all image to UndoStack
     * @param imageArea corresponse to image, which is edited
     */
    virtual void makeUndoCommand(ImageArea &imageArea);
    
};

#endif // ABSTRACTINSTRUMENT_H
