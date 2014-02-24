

#ifndef RISEZEDIALOG_H
#define RISEZEDIALOG_H

#include <QDialog>

QT_BEGIN_NAMESPACE
class QLabel;
class QSpinBox;
class QCheckBox;
QT_END_NAMESPACE

/**
 * @brief QDialog for resizing image.
 *
 */
class ResizeDialog : public QDialog
{
    Q_OBJECT

public:

    explicit ResizeDialog(const QSize &size, QWidget *parent);

    inline QSize getNewSize() { return QSize(mWidth, mHeight); }
    
private:
    void initializeGui();

    QLabel *mNewSizeLabel; /**< Label for showing new size */
    QSpinBox *mPixelWButton, *mPixelHButton,
             *mPercentWButton, *mPercentHButton;
    QCheckBox *mPreserveAspectBox;
    int mWidth, mHeight,
        mOrigWidth, mOrigHeight;

signals:
    
private slots:
    void pixelsButtonClicked(bool flag);
    void percentButtonClicked(bool flag);
    void pixelsWValueChanged(const int &value);
    void pixelsHValueChanged(const int &value);
    void percentWValueChanged(const int &value);
    void percentHValueChanged(const int &value);
    
};

#endif // RISEZEDIALOG_H
