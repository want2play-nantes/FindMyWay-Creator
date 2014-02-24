
#include "imagearea.h"
#include "datasingleton.h"
#include "undocommand.h"

#include "instruments/abstractinstrument.h"
#include "instruments/lineinstrument.h"
#include "instruments/rectangleinstrument.h"
#include "instruments/ellipseinstrument.h"
#include "instruments/magnifierinstrument.h"
#include "instruments/selectioninstrument.h"
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
    mAdditionalTools = new AdditionalTools(this, this->parent());



    mUndoStack = new QUndoStack(this);
    mUndoStack->setUndoLimit(DataSingleton::Instance()->getHistoryDepth());

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
        int width, height;
        width = DataSingleton::Instance()->getBaseSize().width();
        height = DataSingleton::Instance()->getBaseSize().height();
        if (DataSingleton::Instance()->getIsInitialized() &&
            DataSingleton::Instance()->getIsAskCanvasSize())
        {
            QClipboard *globalClipboard = QApplication::clipboard();
            QImage mClipboardImage = globalClipboard->image();
            if (!mClipboardImage.isNull())
            {
                width = mClipboardImage.width();
                height = mClipboardImage.height();
            }
            ResizeDialog resizeDialog(QSize(width, height), this);
            if(resizeDialog.exec() != QDialog::Accepted)
                return;
            QSize newSize = resizeDialog.getNewSize();
            width = newSize.width();
            height = newSize.height();
            mAdditionalTools->resizeCanvas(width, height, false);
            mIsEdited = false;
        }
        QPainter *painter = new QPainter(mImage);
        painter->fillRect(0, 0, width, height, Qt::white);
        painter->end();

        resize(mImage->rect().right() + 6,
               mImage->rect().bottom() + 6);
        mFilePath = QString(""); // empty name indicate that user has accepted tab creation
    }

    QTimer *autoSaveTimer = new QTimer(this);
    autoSaveTimer->setInterval(DataSingleton::Instance()->getAutoSaveInterval() * 1000);
    connect(autoSaveTimer, SIGNAL(timeout()), this, SLOT(autoSave()));
    connect(mAdditionalTools, SIGNAL(sendNewImageSize(QSize)), this, SIGNAL(sendNewImageSize(QSize)));

    autoSaveTimer->start();

    SelectionInstrument *selectionInstrument = new SelectionInstrument(this);
    connect(selectionInstrument, SIGNAL(sendEnableCopyCutActions(bool)), this, SIGNAL(sendEnableCopyCutActions(bool)));
    connect(selectionInstrument, SIGNAL(sendEnableSelectionInstrument(bool)), this, SIGNAL(sendEnableSelectionInstrument(bool)));

    // Instruments handlers
    mInstrumentsHandlers.fill(0, (int)INSTRUMENTS_COUNT);
    mInstrumentsHandlers[CURSOR] = selectionInstrument;
    mInstrumentsHandlers[LINE] = new LineInstrument(this);
    mInstrumentsHandlers[RECTANGLE] = new RectangleInstrument(this);
    mInstrumentsHandlers[ELLIPSE] = new EllipseInstrument(this);
    mInstrumentsHandlers[MAGNIFIER] = new MagnifierInstrument(this);

}

ImageArea::~ImageArea()
{

}

void ImageArea::initializeImage()
{
    mImage = new QImage(DataSingleton::Instance()->getBaseSize(),
                        QImage::Format_ARGB32_Premultiplied);
}

void ImageArea::open()
{
    QString fileName(mFilePath);
    QFileDialog dialog(this, tr("Open image..."), "", mOpenFilter);
    QString prevPath = DataSingleton::Instance()->getLastFilePath();

    if (!prevPath.isEmpty())
        dialog.selectFile(prevPath);
    else
        dialog.setDirectory(QDir::homePath());

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
        DataSingleton::Instance()->setLastFilePath(filePath);
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
    clearSelection();
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
    clearSelection();
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
    if(mIsEdited && !mFilePath.isEmpty() && DataSingleton::Instance()->getIsAutoSave())
    {
        if(mImage->save(mFilePath)) {
            mIsEdited = false;
        }
    }
}

void ImageArea::resizeImage()
{
    mAdditionalTools->resizeImage();
    emit sendNewImageSize(mImage->size());
}

void ImageArea::resizeCanvas()
{
    mAdditionalTools->resizeCanvas(mImage->width(), mImage->height(), true);
    emit sendNewImageSize(mImage->size());
}

void ImageArea::rotateImage(bool flag)
{
    mAdditionalTools->rotateImage(flag);
    emit sendNewImageSize(mImage->size());
}



bool ImageArea::zoomImage(qreal factor)
{
    return mAdditionalTools->zoomImage(factor);
}

void ImageArea::copyImage()
{
    SelectionInstrument *instrument = static_cast <SelectionInstrument*> (mInstrumentsHandlers.at(CURSOR));
    instrument->copyImage(*this);
}

void ImageArea::pasteImage()
{
    if(DataSingleton::Instance()->getInstrument() != CURSOR)
        emit sendSetInstrument(CURSOR);
    SelectionInstrument *instrument = static_cast <SelectionInstrument*> (mInstrumentsHandlers.at(CURSOR));
    instrument->pasteImage(*this);
}

void ImageArea::cutImage()
{
    SelectionInstrument *instrument = static_cast <SelectionInstrument*> (mInstrumentsHandlers.at(CURSOR));
    instrument->cutImage(*this);
}


void ImageArea::mouseMoveEvent(QMouseEvent *event)
{
    InstrumentsEnum instrument = DataSingleton::Instance()->getInstrument();
    mInstrumentHandler = mInstrumentsHandlers.at(DataSingleton::Instance()->getInstrument());
    if(mIsResize)
    {
         mAdditionalTools->resizeCanvas(event->x(), event->y());
         emit sendNewImageSize(mImage->size());
    }
    else if(event->pos().x() < mImage->rect().right() + 6 &&
            event->pos().x() > mImage->rect().right() &&
            event->pos().y() > mImage->rect().bottom() &&
            event->pos().y() < mImage->rect().bottom() + 6)
    {
        setCursor(Qt::SizeFDiagCursor);
        if (qobject_cast<AbstractSelection*>(mInstrumentHandler))
            return;
    }
    else if (!qobject_cast<AbstractSelection*>(mInstrumentHandler))
    {
        restoreCursor();
    }
    if(event->pos().x() < mImage->width() &&
            event->pos().y() < mImage->height())
    {
        emit sendCursorPos(event->pos());
    }

    if(instrument != NONE_INSTRUMENT)
    {
        mInstrumentHandler->mouseMoveEvent(event, *this);
    }
}

void ImageArea::mouseReleaseEvent(QMouseEvent *event)
{
    if(mIsResize)
    {
       mIsResize = false;
       restoreCursor();
    }
    else if(DataSingleton::Instance()->getInstrument() != NONE_INSTRUMENT)
    {
        mInstrumentHandler = mInstrumentsHandlers.at(DataSingleton::Instance()->getInstrument());
        mInstrumentHandler->mouseReleaseEvent(event, *this);
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




void ImageArea::restoreCursor()
{
    switch(DataSingleton::Instance()->getInstrument())
    {
    case INSTRUMENTS_COUNT:
        break;
    case MAGNIFIER:
        mPixmap = new QPixmap(":/media/instruments-icons/cursor_loupe.png");
        mCurrentCursor = new QCursor(*mPixmap);
        setCursor(*mCurrentCursor);
        break;
    case NONE_INSTRUMENT:
        mCurrentCursor = new QCursor(Qt::ArrowCursor);
        setCursor(*mCurrentCursor);
        break;
    case CURSOR:
        mCurrentCursor = new QCursor(Qt::CrossCursor);
        setCursor(*mCurrentCursor);
        break;

    case RECTANGLE: case ELLIPSE: case LINE:
        mCurrentCursor = new QCursor(Qt::CrossCursor);
        setCursor(*mCurrentCursor);
        break;

    }
}

void ImageArea::drawCursor()
{
    QPainter painter;
    mPixmap = new QPixmap(25, 25);
    QPoint center(13, 13);
    switch(DataSingleton::Instance()->getInstrument())
    {
    case NONE_INSTRUMENT: case LINE: case MAGNIFIER:
case RECTANGLE: case ELLIPSE: case CURSOR: case INSTRUMENTS_COUNT:

        break;

    }
    painter.begin(mPixmap);
    switch(DataSingleton::Instance()->getInstrument())
    {
    case NONE_INSTRUMENT: case LINE: case MAGNIFIER:
    case RECTANGLE: case ELLIPSE: case CURSOR: case INSTRUMENTS_COUNT:

        break;

        painter.drawEllipse(center, DataSingleton::Instance()->getPenSize()/2,
                        DataSingleton::Instance()->getPenSize()/2);
        break;

    }
    painter.setPen(Qt::black);
    painter.drawPoint(13, 13);
    painter.drawPoint(13, 3);
    painter.drawPoint(13, 5);
    painter.drawPoint(13, 21);
    painter.drawPoint(13, 23);
    painter.drawPoint(3, 13);
    painter.drawPoint(5, 13);
    painter.drawPoint(21, 13);
    painter.drawPoint(23, 13);
    painter.setPen(Qt::white);
    painter.drawPoint(13, 12);
    painter.drawPoint(13, 14);
    painter.drawPoint(12, 13);
    painter.drawPoint(14, 13);
    painter.drawPoint(13, 4);
    painter.drawPoint(13, 6);
    painter.drawPoint(13, 20);
    painter.drawPoint(13, 22);
    painter.drawPoint(4, 13);
    painter.drawPoint(6, 13);
    painter.drawPoint(20, 13);
    painter.drawPoint(22, 13);
    painter.end();
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

void ImageArea::saveImageChanges()
{
    foreach (AbstractInstrument* instrument, mInstrumentsHandlers)
    {
        if (AbstractSelection *selection = qobject_cast<AbstractSelection*>(instrument))
            selection->saveImageChanges(*this);
    }
}

void ImageArea::clearSelection()
{
    foreach (AbstractInstrument* instrument, mInstrumentsHandlers)
    {
        if (AbstractSelection *selection = qobject_cast<AbstractSelection*>(instrument))
            selection->clearSelection(*this);
    }
}

void ImageArea::pushUndoCommand(UndoCommand *command)
{
    if(command != 0)
        mUndoStack->push(command);
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
    else if(DataSingleton::Instance()->getInstrument() != NONE_INSTRUMENT)
    {
        mInstrumentHandler = mInstrumentsHandlers.at(DataSingleton::Instance()->getInstrument());
        mInstrumentHandler->mousePressEvent(event, *this);
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


