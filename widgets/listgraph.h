#ifndef LIST_GRAPH_H
#define LIST_GRAPH_H
#include <QTreeView>
#include <QMessageBox>
#include <QStandardItemModel>
#include <QStandardItem>
#include <QVBoxLayout>
#include <QHeaderView>
#include <QString>
#include <QFileInfo>

class ListGraph:public QTreeView
{
      Q_OBJECT
public:
    ListGraph(QWidget *_p);
    QStandardItem *addItem(QString _nom);
    QStandardItem *addItem(QStandardItem* _item_p,QString& f);
   // QStandardItem* ajouter_une_sol(QStandardItem* _item_p,solution *);

    int get_session_item(QStandardItem *_item_fils, QStandardItem*& _item_session);

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

#endif // LIST_GRAPH_H
