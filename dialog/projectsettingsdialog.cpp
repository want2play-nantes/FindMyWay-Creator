
#include "projectsettingsdialog.h"
#include "ui_projectsettingsdialog.h"

#include <QMessageBox>

ProjectSettingsDialog::ProjectSettingsDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ProjectSettingsDialog),
    ufrRef(10),
    building(1),
    floor(0)
{
    ui->setupUi(this);
    ui->ufrRef->setValue(this->ufrRef);
    ui->buildingNumber->setValue(this->building);
    ui->floor->setValue(this->floor);

    refreshFileName();
}

ProjectSettingsDialog::~ProjectSettingsDialog()
{
    delete ui;
}

QString ProjectSettingsDialog::getMapPath() const { return mapPath; }
void ProjectSettingsDialog::setMapPath(const QString &value) { mapPath = value; }

QString ProjectSettingsDialog::getFileName() const { return fileName; }

int ProjectSettingsDialog::getUfrRef() const { return ufrRef; }
void ProjectSettingsDialog::setUfrRef(int value) { ufrRef = value; }

int ProjectSettingsDialog::getFloor() const { return floor; }
void ProjectSettingsDialog::setFloor(int value) { floor = value; }

int ProjectSettingsDialog::getBuilding() const { return building; }
void ProjectSettingsDialog::setBuilding(int value) { building = value; }

void ProjectSettingsDialog::refreshFileName()
{
    QString tFileName = QString::number(ufrRef) + "_";

    if (building < 10)
        tFileName += "0" + QString::number(building) + "_";
    else
        tFileName += QString::number(building) + "_";

    if (floor >= 0)
        tFileName += "0" + QString::number(floor);
    else
        tFileName += "S" + QString::number(-floor - 1);

    this->fileName = tFileName;
    ui->fileName->setText(tFileName + ".unmap");
}

void ProjectSettingsDialog::on_ufrRef_valueChanged(int value)
{
    this->ufrRef = value;
    refreshFileName();
}


void ProjectSettingsDialog::on_buildingNumber_valueChanged(int value)
{
    this->building = value;
    refreshFileName();
}


void ProjectSettingsDialog::on_floor_valueChanged(int value)
{
    this->floor = value;
    refreshFileName();
}


void ProjectSettingsDialog::on_browseButton_released()
{
    mapPath = QFileDialog::getOpenFileName(this, tr("Ouvrir le plan assosié au fichier"),"./",tr("Images (*.png *.jpg *.jpeg)"));
    ui->mapPath->setText(this->mapPath);
}

