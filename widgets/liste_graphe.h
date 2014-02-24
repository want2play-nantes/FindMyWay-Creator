#ifndef LISTE_GRAPHE_H
#define LISTE_GRAPHE_H
#include <QTreeView>
#include <QMessageBox>
#include <QStandardItemModel>
#include <QStandardItem>
#include <QVBoxLayout>
#include <QHeaderView>
#include <QString>
#include <QFileInfo>

//#include "visu_graphe.h"

class liste_graphe:public QTreeView
{
      Q_OBJECT
public:
    liste_graphe(QWidget *_p);
    QStandardItem* nouveau_liste_item(QString _nom);
    QStandardItem* ajouter_une_inst(QStandardItem* _item_p,QString& f);
   // QStandardItem* ajouter_une_sol(QStandardItem* _item_p,solution *);

    int get_session_item(QStandardItem *_item_fils,QStandardItem*& _item_session);


    QStandardItemModel *_modele;// modele
    QStandardItem *_root; // item root
    QStandardItem *_m; // item root
private :
    int idx_item;
    int selected_item_id;

signals:
     void item_selected(QStandardItem*,QStandardItem*);

     //void affiche_info_graphe(QStandardItem*,QString);

 private slots:
     void item_selected_slot(QModelIndex _idx);
};

#endif // LISTE_GRAPHE_H
