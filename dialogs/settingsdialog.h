
#ifndef SETTINGSDIALOG_H
#define SETTINGSDIALOG_H


#include <QDialog>

class QDragEnterEvent;
class QDropEvent;
class QSpinBox;

class SettingsDialog : public QDialog
{
public:
    SettingsDialog(QWidget *parent=0);
    QString nomDeFichier;
     QSpinBox *mPercentHButton;

protected:


};


#endif // SETTINGSDIALOG_H
