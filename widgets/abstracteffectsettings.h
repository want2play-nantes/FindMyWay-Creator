
#ifndef ABSTRACTEFFECTWIDGET_H
#define ABSTRACTEFFECTWIDGET_H

#include <QWidget>

class AbstractEffectSettings : public QWidget
{
    Q_OBJECT
signals:
    void matrixChanged();
public:
    explicit AbstractEffectSettings(QWidget *parent = 0) : QWidget(parent) {}
    
    QList<double> virtual getConvolutionMatrix() = 0;
};

#endif // ABSTRACTEFFECTWIDGET_H
