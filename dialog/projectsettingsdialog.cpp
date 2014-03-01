
#include "projectsettingsdialog.h"
#include "ui_projectsettingsdialog.h"

ProjectSettingsDialog::ProjectSettingsDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ProjectSettingsDialog),
    ufrRef(10),
    building(1),
    floor(0),
    part(0),
    map(NULL)
{
    ui->setupUi(this);
    ui->ufrRef->setValue(this->ufrRef);
    ui->buildingNumber->setValue(this->building);
    ui->floor->setValue(this->floor);

    // TODO : Déforme l'image, il faut scaler manuellement ou trouver mieux
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

void ProjectSettingsDialog::setEditable(Map * map)
{
    this->map = map;

    ui->ufrRef->setValue(map->getUfrRef());
    ui->buildingNumber->setValue(map->getBuilding());
    ui->floor->setValue(map->getFloor());

    if (map->getPart() > 0)
    {
        ui->part->setEnabled(true);
        ui->part->setValue(map->getPart());
    }

    ui->imagePreview->setPixmap(*map->getImg());

    ui->browseButton->setEnabled(false);
    ui->buttonBox->button(QDialogButtonBox::Ok)->setEnabled(true);
}


QString ProjectSettingsDialog::getFileName() const { return fileName; }

int ProjectSettingsDialog::getUfrRef() const { return ufrRef; }
void ProjectSettingsDialog::setUfrRef(int value) { ufrRef = value; }

int ProjectSettingsDialog::getFloor() const { return floor; }
void ProjectSettingsDialog::setFloor(int value) { floor = value; }

int ProjectSettingsDialog::getBuilding() const { return building; }
void ProjectSettingsDialog::setBuilding(int value) { building = value; }

int ProjectSettingsDialog::getPart() const { return part; }
void ProjectSettingsDialog::setPart(const int &value) { part = value; }

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

    if (part != 0) {
        tFileName += QString(QChar(part+96));
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

        // TODO : Ne fonctionne pas, l'image n'est pas scale
        image.scaled(ui->imagePreview->width(), ui->imagePreview->height(), Qt::KeepAspectRatio);


        ui->imagePreview->setPixmap(image);
    }
}

void ProjectSettingsDialog::on_partCheckBox_stateChanged(int status)
{
    if (status == Qt::Checked)
    {
        ui->part->setEnabled(true);
        part = ui->part->value();
    }
    else if (status == Qt::Unchecked)
    {
        ui->part->setEnabled(false);
        part = 0;
    }

    refreshFileName();
}

void ProjectSettingsDialog::on_part_valueChanged(int value)
{
    this->part = value;
    refreshFileName();
}

void ProjectSettingsDialog::on_buttonBox_accepted()
{
    if (map) {
        map->setFileName(fileName);
        map->setUfrRef(ufrRef);
        map->setBuilding(building);
        map->setFloor(floor);
        map->setPart(part);
    }
}
