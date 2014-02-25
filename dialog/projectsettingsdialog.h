#ifndef PROJECTSETTINGSDIALOG_H
#define PROJECTSETTINGSDIALOG_H

#include <QDialog>
#include <QFileDialog>


namespace Ui {
class ProjectSettingsDialog;
}

class ProjectSettingsDialog : public QDialog
{
    Q_OBJECT
    
public:
    explicit ProjectSettingsDialog(QWidget *parent = 0);
    ~ProjectSettingsDialog();
    
private slots:
    void onUfrRefValueChanged(int value);
    void onBuildingNumberValueChanged(int value);
    void onFloorValueChanged(int value);

    void refreshFileName();

    void onBrowseButtonReleased();

private:
    Ui::ProjectSettingsDialog *ui;

    int building, floor, ufrRef;
    QString fileName, mapPath;
};

#endif // PROJECTSETTINGSDIALOG_H
