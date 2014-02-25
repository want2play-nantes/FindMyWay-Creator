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
    
    int getBuilding() const;
    void setBuilding(int value);

    int getFloor() const;
    void setFloor(int value);

    int getUfrRef() const;
    void setUfrRef(int value);

    QString getFileName() const;

    QString getMapPath() const;
    void setMapPath(const QString &value);

private slots:
    void on_ufrRef_valueChanged(int value);

    void on_buildingNumber_valueChanged(int value);

    void on_floor_valueChanged(int value);

    void on_browseButton_released();


private:
    Ui::ProjectSettingsDialog *ui;

    int building;
    int floor;
    int ufrRef;
    QString fileName;
    QString mapPath;

    void refreshFileName();
};

#endif // PROJECTSETTINGSDIALOG_H
