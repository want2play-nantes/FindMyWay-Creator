#include <QPushButton>
#include<QLabel>
#include <QGridLayout>
#include <QLineEdit>
#include "settingsdialog.h"

SettingsDialog::SettingsDialog(QWidget *parent):QDialog(parent)
    {
    QGridLayout *grid = new QGridLayout;
        // Elle est simplement composé d'un bouton "Fermer"
        QPushButton *closeBtn = new QPushButton("Annuler", this);
        QPushButton *validBtn = new QPushButton("Valider", this);
        QLabel *n = new QLabel("Nom de fichier");
        QLabel *n1 = new QLabel("Numéro du Batiment");
        QLabel *n2 = new QLabel("Numéro de l'etage");
        QLineEdit *m = new QLineEdit();
        QLineEdit *m1 = new QLineEdit();
        QLineEdit *m2 = new QLineEdit();

        nomDeFichier = m->text();
        grid->addWidget(closeBtn,4,1);
        grid->addWidget(validBtn,4,2);
        grid->addWidget(n,0,0);
        grid->addWidget(n1,1,0);
        grid->addWidget(n2,2,0);
        grid->addWidget(m,0,1);
        grid->addWidget(m1,1,1);
        grid->addWidget(m2,2,1);

        this->setLayout(grid);
        // lequel ferme la fenetre lorsqu'on clic dessus
       connect(closeBtn, SIGNAL(clicked()), this, SLOT(close()));
       connect(validBtn, SIGNAL(clicked()), this, SLOT(accept()));
    }

