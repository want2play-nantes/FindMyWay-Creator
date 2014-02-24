
#ifndef GAUSSIANBLURFILTERSETTINGS_H
#define GAUSSIANBLURFILTERSETTINGS_H

#include <QSlider>

#include "abstracteffectsettings.h"

class GaussianBlurFilterSettings : public AbstractEffectSettings
{
    Q_OBJECT
public:
    explicit GaussianBlurFilterSettings(QWidget *parent = 0);
    
protected:
    virtual QList<double> getConvolutionMatrix();

private:
    QSlider *mIntensitySlider;
    
};

#endif // GAUSSIANBLURFILTERSETTINGS_H
