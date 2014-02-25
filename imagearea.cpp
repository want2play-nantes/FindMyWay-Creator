
#include "imagearea.h"

#include "dialogs/resizedialog.h"
#include "instruments/dragwidget.h"

#include <QApplication>
#include <QPainter>
#include <QFileDialog>
#include <QtCore/QDebug>
#include <QMouseEvent>
#include <QPaintEvent>
#include <QPrinter>
#include <QPrintDialog>
#include <QtCore/QTimer>
#include <QImageReader>
#include <QImageWriter>
#include <QUndoStack>
#include <QtCore/QDir>
#include <QMessageBox>
#include <QClipboard>
#include <QMimeData>
#include <QDrag>
ImageArea::ImageArea(const bool &isOpen, const QString &filePath, QWidget *parent) :
    QWidget(parent), mIsEdited(false), mIsPaint(false), mIsResize(false)
{
    //setFrameStyle(QFrame::Sunken | QFrame::StyledPanel);
    setAcceptDrops(true);
       dr = new DragWidget(this);
    setMouseTracking(true);

    mRightButtonPressed = false;
    mFilePath = QString();
    makeFormatsFilters();
    initializeImage();
    mZoomFactor = 1;

    setAcceptDrops(true);

    mZoomedFactor = 1;

    if(isOpen && filePath.isEmpty())
    {
        open();
    }
    else if(isOpen && !filePath.isEmpty())
    {
        open(filePath);
    }
    else
    {
        QPainter *painter = new QPainter(mImage);
        painter->fillRect(0, 0, mImage->width(), mImage->height(), Qt::white);
        painter->end();

        resize(mImage->rect().right() + 6, mImage->rect().bottom() + 6);
        mFilePath = QString(""); // empty name indicate that user has accepted tab creation
    }

    QTimer *autoSaveTimer = new QTimer(this);
    autoSaveTimer->setInterval(300000);
    connect(autoSaveTimer, SIGNAL(timeout()), this, SLOT(autoSave()));

    autoSaveTimer->start();
}

ImageArea::~ImageArea()
{

}

void ImageArea::initializeImage()
{
    mImage = new QImage(QSize(400, 300), QImage::Format_ARGB32_Premultiplied);
}

void ImageArea::open()
{
    QFileDialog dialog(this, tr("Ouvrir une image..."), "", mOpenFilter);

    if (!mLastFilePath.isEmpty()) {
        dialog.setDirectory(mLastFilePath);
    }
    else {
        dialog.setDirectory(QDir::homePath());
    }

    if (dialog.exec())
    {
        QStringList selectedFiles = dialog.selectedFiles();
        if (!selectedFiles.isEmpty())
        {
          open(selectedFiles.takeFirst());
        }
    }
}



void ImageArea::open(const QString &filePath)
{
    QApplication::setOverrideCursor(Qt::WaitCursor);
    if(mImage->load(filePath))
    {
        *mImage = mImage->convertToFormat(QImage::Format_ARGB32_Premultiplied);
        mFilePath = filePath;
        mLastFilePath = filePath;
        resize(mImage->rect().right() + 6,
               mImage->rect().bottom() + 6);
        QApplication::restoreOverrideCursor();
    }
    else
    {
        qDebug()<<QString("Can't open file %1").arg(filePath);
        QApplication::restoreOverrideCursor();
        QMessageBox::warning(this, tr("Error opening file"), tr("Can't open file \"%1\".").arg(filePath));
    }
}

bool ImageArea::save()
{
    if(mFilePath.isEmpty())
    {
        return saveAs();
    }
    //clearSelection();
    if (!mImage->save(mFilePath))
    {
        QMessageBox::warning(this, tr("Error saving file"), tr("Can't save file \"%1\".").arg(mFilePath));
        return false;
    }
    mIsEdited = false;
    return true;
}

bool ImageArea::saveAs()
{
    bool result = true;
    QString filter;
    QString fileName(mFilePath);
    //clearSelection();
    if(fileName.isEmpty())
    {
        fileName = QDir::homePath() + "/" + tr("Untitled image") + ".png";
    }
    QString filePath = QFileDialog::getSaveFileName(this, tr("Save image..."), fileName, mSaveFilter,
                                                    &filter,
                                                    QFileDialog::DontUseNativeDialog);

    QApplication::setOverrideCursor(Qt::WaitCursor);
    //parse file extension
    if(!filePath.isEmpty())
    {
        QString extension;
        //we should test it on windows, because of different slashes
        QString temp = filePath.split("/").last();
        //if user entered some extension
        if(temp.contains('.'))
        {
            temp = temp.split('.').last();
            if(QImageWriter::supportedImageFormats().contains(temp.toLatin1()))
                extension = temp;
            else
                extension = "png"; //if format is unknown, save it as png format, but with user extension
        }
        else
        {
            extension = filter.split('.').last().remove(')');
            filePath += '.' + extension;
        }

        if(mImage->save(filePath, extension.toLatin1().data()))
        {
            mFilePath = filePath;
            mIsEdited = false;
        }
        else
        {
            QMessageBox::warning(this, tr("Error saving file"), tr("Can't save file \"%1\".").arg(filePath));
            result = false;
        }
    }
    QApplication::restoreOverrideCursor();
    return result;
}

void ImageArea::autoSave()
{
    if(mIsEdited && !mFilePath.isEmpty())
    {
        if(mImage->save(mFilePath)) {
            mIsEdited = false;
        }
    }
}

bool ImageArea::zoomImage(qreal factor)
{
    mZoomedFactor *= factor;
    if(mZoomedFactor < 0.25)
    {
        mZoomedFactor = 0.25;
        return false;
    }
    else if(mZoomedFactor > 4)
    {
        mZoomedFactor = 4;
        return false;
    }
    else
    {
        this->setImage(mImage->transformed(QTransform::fromScale(factor, factor)));
        //this->resize((mPImageArea->rect().width())*factor, (mPImageArea->rect().height())*factor);
        this->setEdited(true);
        return true;
    }

}

void ImageArea::mouseMoveEvent(QMouseEvent *event)
{
    if(event->pos().x() < mImage->rect().right() + 6 &&
            event->pos().x() > mImage->rect().right() &&
            event->pos().y() > mImage->rect().bottom() &&
            event->pos().y() < mImage->rect().bottom() + 6)
    {
        setCursor(Qt::SizeFDiagCursor);
    }

    if(event->pos().x() < mImage->width() &&
            event->pos().y() < mImage->height())
    {
        emit sendCursorPos(event->pos());
    }
}

void ImageArea::mouseReleaseEvent(QMouseEvent *event)
{
    if(mIsResize)
    {
       mIsResize = false;
    }
}

void ImageArea::paintEvent(QPaintEvent *event)
{
    QPainter *painter = new QPainter(this);
    //QRect *rect = new QRect(event->rect());

    painter->setBrush(QBrush(QPixmap(":media/textures/transparent.jpg")));
    painter->drawRect(0, 0,
                      mImage->rect().right() - 1,
                      mImage->rect().bottom() - 1);

    painter->drawImage(event->rect(), *mImage, event->rect());

    painter->setPen(Qt::NoPen);
    painter->setBrush(QBrush(Qt::black));
    painter->drawRect(QRect(mImage->rect().right(),
                            mImage->rect().bottom(), 6, 6));

    painter->end();
}

void ImageArea::makeFormatsFilters()
{
    QList<QByteArray> ba = QImageReader::supportedImageFormats();
    //make "all supported" part
    mOpenFilter = "All supported (";
    foreach (QByteArray temp, ba)
        mOpenFilter += "*." + temp + " ";
    mOpenFilter[mOpenFilter.length() - 1] = ')'; //delete last space
    mOpenFilter += ";;";

    //using ";;" as separator instead of "\n", because Qt's docs recomended it :)
    if(ba.contains("png"))
        mOpenFilter += "Portable Network Graphics(*.png);;";
    if(ba.contains("bmp"))
        mOpenFilter += "Windows Bitmap(*.bmp);;";
    if(ba.contains("gif"))
        mOpenFilter += "Graphic Interchange Format(*.gif);;";
    if(ba.contains("jpg") || ba.contains("jpeg"))
        mOpenFilter += "Joint Photographic Experts Group(*.jpg *.jpeg);;";
    if(ba.contains("mng"))
        mOpenFilter += "Multiple-image Network Graphics(*.mng);;";
    if(ba.contains("pbm"))
        mOpenFilter += "Portable Bitmap(*.pbm);;";
    if(ba.contains("pgm"))
        mOpenFilter += "Portable Graymap(*.pgm);;";
    if(ba.contains("ppm"))
        mOpenFilter += "Portable Pixmap(*.ppm);;";
    if(ba.contains("tiff") || ba.contains("tif"))
        mOpenFilter += "Tagged Image File Format(*.tiff, *tif);;";
    if(ba.contains("xbm"))
        mOpenFilter += "X11 Bitmap(*.xbm);;";
    if(ba.contains("xpm"))
        mOpenFilter += "X11 Pixmap(*.xpm);;";
    if(ba.contains("svg"))
        mOpenFilter += "Scalable Vector Graphics(*.svg);;";

    mOpenFilter += "All Files(*.*)";

    //make saveFilter
    ba = QImageWriter::supportedImageFormats();
    if(ba.contains("png"))
        mSaveFilter += "Portable Network Graphics(*.png)";
    if(ba.contains("bmp"))
        mSaveFilter += ";;Windows Bitmap(*.bmp)";
    if(ba.contains("jpg") || ba.contains("jpeg"))
        mSaveFilter += ";;Joint Photographic Experts Group(*.jpg)";
    if(ba.contains("ppm"))
        mSaveFilter += ";;Portable Pixmap(*.ppm)";
    if(ba.contains("tiff") || ba.contains("tif"))
        mSaveFilter += ";;Tagged Image File Format(*.tiff)";
    if(ba.contains("xbm"))
        mSaveFilter += ";;X11 Bitmap(*.xbm)";
    if(ba.contains("xpm"))
        mSaveFilter += ";;X11 Pixmap(*.xpm)";
}

void ImageArea::dragEnterEvent(QDragEnterEvent *event)
{
    if (event->mimeData()->hasFormat("application/x-dnditemdata")) {
        if (event->source() == this) {
            event->setDropAction(Qt::MoveAction);
            event->accept();
        } else {
            event->acceptProposedAction();
        }
    } else {
        event->ignore();
    }
}

void ImageArea::dragMoveEvent(QDragMoveEvent *event)
{
    if (event->mimeData()->hasFormat("application/x-dnditemdata")) {
        if (event->source() == this) {
            event->setDropAction(Qt::MoveAction);
            event->accept();
        } else {
            event->acceptProposedAction();
        }
    } else {
        event->ignore();
    }
}

void ImageArea::dropEvent(QDropEvent *event)
{
    if (event->mimeData()->hasFormat("application/x-dnditemdata")) {
        QByteArray itemData = event->mimeData()->data("application/x-dnditemdata");
        QDataStream dataStream(&itemData, QIODevice::ReadOnly);

        QPixmap pixmap;
        QPoint offset;
        dataStream >> pixmap >> offset;

        QLabel *newIcon = new QLabel(this);
        newIcon->setPixmap(pixmap);
        newIcon->move(event->pos() - offset);
        newIcon->show();
        newIcon->setAttribute(Qt::WA_DeleteOnClose);

        if (event->source() == this) {
            event->setDropAction(Qt::MoveAction);
            event->accept();
        } else {
            event->acceptProposedAction();
        }
    } else {
        event->ignore();
    }
}

void ImageArea::mousePressEvent(QMouseEvent *event)
{
    if(event->button() == Qt::LeftButton &&
            event->pos().x() < mImage->rect().right() + 6 &&
            event->pos().x() > mImage->rect().right() &&
            event->pos().y() > mImage->rect().bottom() &&
            event->pos().y() < mImage->rect().bottom() + 6)
    {
        mIsResize = true;
        setCursor(Qt::SizeFDiagCursor);
    }

    QLabel *child = static_cast<QLabel*>(childAt(event->pos()));
    if (!child)
        return;

    QPixmap pixmap = *child->pixmap();

    QByteArray itemData;
    QDataStream dataStream(&itemData, QIODevice::WriteOnly);
    dataStream << pixmap << QPoint(event->pos() - child->pos());

    QMimeData *mimeData = new QMimeData;
    mimeData->setData("application/x-dnditemdata", itemData);

    QDrag *drag = new QDrag(this);
    drag->setMimeData(mimeData);
    drag->setPixmap(pixmap);
    drag->setHotSpot(event->pos() - child->pos());

    QPixmap tempPixmap = pixmap;
    QPainter painter;
    painter.begin(&tempPixmap);
    painter.fillRect(pixmap.rect(), QColor(127, 127, 127, 127));
    painter.end();

    child->setPixmap(tempPixmap);

    if (drag->exec(Qt::CopyAction | Qt::MoveAction, Qt::CopyAction) == Qt::MoveAction)
        child->close();
    else {
        child->show();
        child->setPixmap(pixmap);
    }


}


