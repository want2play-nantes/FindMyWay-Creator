
#include "undocommand.h"

UndoCommand::UndoCommand(const QImage *img, ImageArea &imgArea, QUndoCommand *parent)
    : QUndoCommand(parent), mPrevImage(*img), mImageArea(imgArea)
{
    mCurrImage = mPrevImage;
}

void UndoCommand::undo()
{
    mImageArea.clearSelection();
    mCurrImage = *(mImageArea.getImage());
    mImageArea.setImage(mPrevImage);
    mImageArea.update();
    mImageArea.saveImageChanges();
}

void UndoCommand::redo()
{
    mImageArea.setImage(mCurrImage);
    mImageArea.update();
    mImageArea.saveImageChanges();
}
