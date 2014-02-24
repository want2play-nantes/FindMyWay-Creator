#ifndef ABSTRACTEFFECTSDIALOG_H
#define ABSTRACTEFFECTSDIALOG_H

#include <QDialog>
#include <QPushButton>

#include "../widgets/abstracteffectsettings.h"
#include "../widgets/imagepreview.h"

class EffectSettingsDialog : public QDialog
{
    Q_OBJECT
public:
    explicit EffectSettingsDialog(const QImage &img, AbstractEffectSettings *settingsWidget, QWidget *parent = 0);
    
    inline QImage getChangedImage() { return mImage; }
signals:
    
public slots:

private:
    QPushButton *mOkButton;
    QPushButton *mCancelButton;
    QPushButton *mApplyButton;

    AbstractEffectSettings *mSettingsWidget;
    ImagePreview *mImagePreview;

    QImage mImage;

    QRgb convolutePixel(const QImage &image, int x, int y, const QList<double> &kernelMatrix);

private slots:
    void applyMatrix();
};

#endif // ABSTRACTEFFECTSDIALOG_H
