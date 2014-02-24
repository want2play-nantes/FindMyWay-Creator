
#ifndef UNDOCOMMAND_H
#define UNDOCOMMAND_H

#include <QUndoCommand>
#include <QImage>

#include "imagearea.h"

/**
 * @brief Class which provides undo/redo actions
 *
 * In future it should be changed according to architecture changing
 */
class UndoCommand : public QUndoCommand
{
public:
    UndoCommand(const QImage* img, ImageArea &imgArea, QUndoCommand *parent = 0);

    virtual void undo();
    virtual void redo();
private:
    QImage mPrevImage;
    QImage mCurrImage;
    ImageArea& mImageArea;
};

#endif // UNDOCOMMAND_H
