
#include <QLabel>
#include <QLayout>

#include "gaussianblurfiltersettings.h"


GaussianBlurFilterSettings::GaussianBlurFilterSettings(QWidget *parent) :
    AbstractEffectSettings(parent)
{
    QLabel *label = new QLabel(tr("Intensity"), this);

    mIntensitySlider = new QSlider(Qt::Horizontal, this);
    mIntensitySlider->setTickPosition(QSlider::TicksBothSides);
    mIntensitySlider->setMinimum(1);
    mIntensitySlider->setMaximum(10);
    mIntensitySlider->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Fixed);
    connect(mIntensitySlider, SIGNAL(valueChanged(int)), this, SIGNAL(matrixChanged()));

    QVBoxLayout *vLayout = new QVBoxLayout();

    vLayout->addWidget(label);
    vLayout->addWidget(mIntensitySlider);
    vLayout->addStretch();

    setLayout(vLayout);
}

QList<double> GaussianBlurFilterSettings::getConvolutionMatrix()
{
    QList<double> matrix;
    int intensity = mIntensitySlider->value();

    matrix << 1 * intensity << 2 * intensity << 1 * intensity
           << 2 * intensity << 4 * intensity << 2 * intensity
           << 1 * intensity << 2 * intensity << 1 * intensity;

    return matrix;
}
