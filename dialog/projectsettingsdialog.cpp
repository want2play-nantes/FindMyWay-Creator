
#include "projectsettingsdialog.h"
#include "ui_projectsettingsdialog.h"

#include <QMessageBox>

ProjectSettingsDialog::ProjectSettingsDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ProjectSettingsDialog),
    ufrRef(10),
    building(1),
    floor(0),
    editable(true)
{
    ui->setupUi(this);
    ui->ufrRef->setValue(this->ufrRef);
    ui->buildingNumber->setValue(this->building);
    ui->floor->setValue(this->floor);

    ui->imagePreview->setScaledContents(true);

    ui->part->setEnabled(false);

    ui->buttonBox->button(QDialogButtonBox::Ok)->setEnabled(false);

    refreshFileName();

    setFixedWidth(678);
    setFixedHeight(703);
}

ProjectSettingsDialog::~ProjectSettingsDialog()
{
    delete ui;
}

QString ProjectSettingsDialog::getMapPath() const { return mapPath; }
void ProjectSettingsDialog::setMapPath(const QString &value) { mapPath = value; }

bool ProjectSettingsDialog::getEditable() const { return editable; }

void ProjectSettingsDialog::setEditable(bool value)
{
    editable = value;

    if (!editable) {
        ui->browseButton->setEnabled(false);
    }
    else {
        ui->browseButton->setEnabled(true);
    }
}


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

    if (!part.isEmpty()) {
        tFileName += part;
    }

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
    QFileDialog dialog(this, tr("Ouvrir le plan assosié au fichier"), QDir::home().absolutePath(),tr("Images (*.png *.jpg *.jpeg)"));

    if (dialog.exec())
    {
        QStringList selectedFiles = dialog.selectedFiles();
        if (!selectedFiles.isEmpty())
        {
            mapPath = selectedFiles.takeFirst();
            ui->mapPath->setText(this->mapPath);

            ui->buttonBox->button(QDialogButtonBox::Ok)->setEnabled(true);
        }
    }
}

void ProjectSettingsDialog::on_mapPath_textChanged(const QString &text)
{
    QFile file(text);
    if (text.isEmpty() || !file.exists()) {
        ui->imagePreview->setText("Aperçu du plan");
    }
    else
    {
        QPixmap image(text);

        // Ne fonctionne pas, l'image n'est pas scale
        image.scaled(125, 75, Qt::KeepAspectRatio, Qt::FastTransformation);

        ui->imagePreview->setPixmap(image);
    }
}

void ProjectSettingsDialog::on_partCheckBox_stateChanged(int status)
{
    if (status == Qt::Checked)
    {
        ui->part->setEnabled(true);
        part = QString(QChar(ui->part->value()+96));
    }
    else if (status == Qt::Unchecked)
    {
        ui->part->setEnabled(false);
        part = "";
    }

    refreshFileName();
}

void ProjectSettingsDialog::on_part_valueChanged(int value)
{
    this->part = QString(QChar(ui->part->value()+96));
    refreshFileName();
}
