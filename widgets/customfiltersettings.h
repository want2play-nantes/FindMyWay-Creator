
#ifndef CUSTOMFILTERSETTINGS_H
#define CUSTOMFILTERSETTINGS_H

#include <QWidget>
#include <QSpinBox>

#include "abstracteffectsettings.h"

class CustomFilterSettings : public AbstractEffectSettings
{
    Q_OBJECT
public:
    explicit CustomFilterSettings(QWidget *parent = 0);
    
    QList<double> virtual getConvolutionMatrix();

private:
    QDoubleSpinBox *mSpinBox_11;
    QDoubleSpinBox *mSpinBox_12;
    QDoubleSpinBox *mSpinBox_13;
    QDoubleSpinBox *mSpinBox_21;
    QDoubleSpinBox *mSpinBox_22;
    QDoubleSpinBox *mSpinBox_23;
    QDoubleSpinBox *mSpinBox_31;
    QDoubleSpinBox *mSpinBox_32;
    QDoubleSpinBox *mSpinBox_33;

    QDoubleSpinBox* createSpinBox();
};

#endif // CUSTOMFILTERSETTINGS_H
