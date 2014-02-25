
#ifndef IMAGEAREA_H
#define IMAGEAREA_H

#include "instruments/dragwidget.h"
#include <QWidget>
#include <QImage>
#include <QFrame>

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

    inline QString getFileName() { return (mFilePath.isEmpty() ? mFilePath : mFilePath.split('/').last()); }
    inline QImage* getImage() { return mImage; }

    inline void setImage(const QImage &image) { *mImage = image; }

    inline void setEdited(bool flag) { mIsEdited = flag; }

    inline bool getEdited() { return mIsEdited; }

    bool zoomImage(qreal factor);
    inline void setZoomFactor(qreal factor) { mZoomFactor *= factor; }
    inline qreal getZoomFactor() { return mZoomFactor; }
    
private:

    void initializeImage();

    void open();

    void open(const QString &filePath);

    void makeFormatsFilters();

    QImage *mImage,  /**< Main image. */
           mImageCopy; /**< Copy of main image, need for events. */ // ?????????????
    QString mFilePath; /**< Path where located image. */
    QString mOpenFilter; /**< Supported open formats filter. */
    QString mSaveFilter; /**< Supported save formats filter. */
    bool mIsEdited, mIsPaint, mIsResize, mRightButtonPressed;
    QPixmap *mPixmap;
    QCursor *mCurrentCursor;
    qreal mZoomFactor;

    QString mLastFilePath;
    DragWidget *dr;

    qreal mZoomedFactor;

signals:



    void sendNewImageSize(const QSize&);
    void sendCursorPos(const QPoint&);
    void sendRestorePreviousInstrument();

    void sendEnableCopyCutActions(bool enable);

    void sendEnableSelectionInstrument(bool enable);
    
private slots:
    void autoSave();

protected:
    //void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
    void paintEvent(QPaintEvent *event);
    void dragEnterEvent(QDragEnterEvent *event);
    void dragMoveEvent(QDragMoveEvent *event);
    void dropEvent(QDropEvent *event);
    void mousePressEvent(QMouseEvent *event);





};

#endif // IMAGEAREA_H
