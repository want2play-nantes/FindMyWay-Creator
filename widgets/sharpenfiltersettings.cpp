
#include <QLabel>
#include <QLayout>

#include "sharpenfiltersettings.h"


SharpenFilterSettings::SharpenFilterSettings(QWidget *parent) :
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

QList<double> SharpenFilterSettings::getConvolutionMatrix()
{
    QList<double> matrix;
    int intensity = mIntensitySlider->value();

    matrix << 0            << -(intensity)        << 0
           << -(intensity) << (intensity * 4) + 1 << -(intensity)
           << 0            << -(intensity)        << 0;

    return matrix;
}
