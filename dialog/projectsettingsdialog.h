#ifndef PROJECTSETTINGSDIALOG_H
#define PROJECTSETTINGSDIALOG_H

#include <QDialog>
#include <QFileDialog>
#include <QCloseEvent>
#include <QLabel>
#include <QPixmap>
#include <QFile>
#include <QMessageBox>

#include "core/map.h"

namespace Ui {
    class ProjectSettingsDialog;
}

class ProjectSettingsDialog : public QDialog
{
    Q_OBJECT
    
public:
    explicit ProjectSettingsDialog(QWidget *parent = 0);
    ~ProjectSettingsDialog();
    
    int getBuilding() const;
    void setBuilding(int value);

    int getFloor() const;
    void setFloor(int value);

    int getUfrRef() const;
    void setUfrRef(int value);

    QString getFileName() const;

    QString getMapPath() const;
    void setMapPath(const QString &value);

    void setEditable(Map *map);

    int getPart() const;
    void setPart(const int &value);

private slots:
    void on_ufrRef_valueChanged(int value);

    void on_buildingNumber_valueChanged(int value);

    void on_floor_valueChanged(int value);

    void on_browseButton_released();

    void on_mapPath_textChanged(const QString &arg1);

    void on_partCheckBox_stateChanged(int arg1);

    void on_part_valueChanged(int arg1);

    void on_buttonBox_accepted();

private:
    Ui::ProjectSettingsDialog *ui;

    int building;
    int floor;
    int ufrRef;
    int part;
    QString fileName;
    QString mapPath;

    Map * map;

    void refreshFileName();
};

#endif // PROJECTSETTINGSDIALOG_H
