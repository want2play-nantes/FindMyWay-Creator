#include "projectsettingsdialog.h"
#include "ui_projectsettingsdialog.h"

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

void ProjectSettingsDialog::onUfrRefValueChanged(int value)
{
    this->ufrRef = value;
    refreshFileName();
}

void ProjectSettingsDialog::onBuildingNumberValueChanged(int value)
{
    this->building = value;
    refreshFileName();
}


void ProjectSettingsDialog::onFloorValueChanged(int value)
{
    this->floor = value;
    refreshFileName();
}

void ProjectSettingsDialog::refreshFileName()
{
    fileName = QString::number(ufrRef) + "_";

    if (building < 10)
        fileName += "0" + QString::number(building) + "_";
    else
        fileName += QString::number(building) + "_";

    if (floor >= 0)
        fileName += "0" + QString::number(floor);
    else
        fileName += "S" + QString::number(-floor - 1);

    ui->fileName->setText(fileName + ".unmap");
}

void ProjectSettingsDialog::onBrowseButtonReleased()
{
    mapPath = QFileDialog::getOpenFileName(this, tr("Ouvrir le plan assosié au fichier"),"/",tr("Images (*.png *.jpg *.jpeg)"));
    ui->mapPath->setText(this->mapPath);
}
