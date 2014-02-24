
#ifndef IMAGEAREA_H
#define IMAGEAREA_H

#include "findmywayenums.h"
#include "additionaltools.h"
#include "instruments/dragwidget.h"
#include <QWidget>
#include <QImage>


QT_BEGIN_NAMESPACE
class QUndoStack;
QT_END_NAMESPACE

class UndoCommand;
class AbstractInstrument;
class AbstractEffect;
class QDragEnterEvent;
class QDropEvent;

class ImageArea : public QWidget
{
    Q_OBJECT

public:

    explicit ImageArea(const bool &isOpen, const QString &filePath, QWidget *parent);
    ~ImageArea();

    bool save();

    bool saveAs();

    void resizeImage();

    void resizeCanvas();

    void rotateImage(bool flag);

    inline QString getFileName() { return (mFilePath.isEmpty() ? mFilePath :
                                           mFilePath.split('/').last()); }
    inline QImage* getImage() { return mImage; }
    inline void setImage(const QImage &image) { *mImage = image; }

    inline void setEdited(bool flag) { mIsEdited = flag; }

    inline bool getEdited() { return mIsEdited; }

    void restoreCursor();

    bool zoomImage(qreal factor);
    inline void setZoomFactor(qreal factor) { mZoomFactor *= factor; }
    inline qreal getZoomFactor() { return mZoomFactor; }
    inline QUndoStack* getUndoStack() { return mUndoStack; }
    inline void setIsPaint(bool isPaint) { mIsPaint = isPaint; }
    inline bool isPaint() { return mIsPaint; }
    inline void emitRestorePreviousInstrument() { emit sendRestorePreviousInstrument(); }

    /**
     * @brief Copying image to the clipboard.
     *
     */
    void copyImage();
    /**
     * @brief Paste image from the clipboard.
     *
     */
    void pasteImage();
    /**
     * @brief Cut image to the clipboard.
     *
     */
    void cutImage();
    /**
     * @brief Save all image changes to image copy.
     *
     */
    void saveImageChanges();

    void clearSelection();

    void pushUndoCommand(UndoCommand *command);
    
private:

    void initializeImage();

    void open();

    void open(const QString &filePath);

    void drawCursor();

    void makeFormatsFilters();

    QImage *mImage,  /**< Main image. */
           mImageCopy; /**< Copy of main image, need for events. */ // ?????????????
    AdditionalTools *mAdditionalTools;
    QString mFilePath; /**< Path where located image. */
    QString mOpenFilter; /**< Supported open formats filter. */
    QString mSaveFilter; /**< Supported save formats filter. */
    bool mIsEdited, mIsPaint, mIsResize, mRightButtonPressed;
    QPixmap *mPixmap;
    QCursor *mCurrentCursor;
    qreal mZoomFactor;
    QUndoStack *mUndoStack;
    QVector<AbstractInstrument*> mInstrumentsHandlers;
    AbstractInstrument *mInstrumentHandler;
    QVector<AbstractEffect*> mEffectsHandlers;
    AbstractEffect *mEffectHandler;
    DragWidget *dr;

signals:



    void sendNewImageSize(const QSize&);
    void sendCursorPos(const QPoint&);
    void sendRestorePreviousInstrument();

    void sendSetInstrument(InstrumentsEnum);

    void sendEnableCopyCutActions(bool enable);

    void sendEnableSelectionInstrument(bool enable);
    
private slots:
    void autoSave();

protected:
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
    void paintEvent(QPaintEvent *event);





};

#endif // IMAGEAREA_H
