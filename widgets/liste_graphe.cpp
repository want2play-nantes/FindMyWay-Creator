#include "liste_graphe.h"
//------------------------------------------------------------------------
//...
//------------------------------------------------------------------------
liste_graphe::liste_graphe(QWidget *_p):QTreeView(_p)
{
    idx_item=1;
    selected_item_id=-1;

    QVBoxLayout *_layout =new QVBoxLayout;

    _modele=new QStandardItemModel;

    _root=new QStandardItem(tr("Sessions"));

    _root->setEditable(false);
    _root->setIcon(QIcon(":/liste/logos/root.gif"));

    //_modele->setItem(0,_root);
    _modele->appendRow(_root);

    _modele->setHeaderData(0, Qt::Horizontal, tr("List :"));

    //liaison modele - vue
    setModel(_modele);
    setLayout(_layout);

    //cacher l'entete du liste
    header()->setHidden(true);

    connect(this,SIGNAL(doubleClicked(QModelIndex)),this,SLOT(item_selected_slot(QModelIndex)));
}

//------------------------------------------------------------------------
// inserer un nouveau liste item.
//------------------------------------------------------------------------
QStandardItem* liste_graphe::nouveau_liste_item(QString _nom=0)
{
    char *_buff=new char[512];
    //recuperer le nom du fichier..

    QString _nom_item;

    if(_nom !=NULL)
    {
        _nom_item=_nom;
    }
    else
    {
        _nom_item=QString("Session_").arg(idx_item);
        //idx
        idx_item++;
    }

    QStandardItem *_item=new QStandardItem(_nom_item);
    _item->setIcon(QIcon(":/liste/logos/session.gif"));
    _item->setAccessibleText("fichier");
    _root->appendRow(_item);

    //---------------------------------------
    //selectioner la session creer.
    this->selectionModel()->clearSelection();

    QModelIndex _id_select=_item->index();
    QItemSelection selection2(_id_select, _id_select);
    this->selectionModel()->select(selection2, QItemSelectionModel::Select);

    this->setCurrentIndex(_item->index());

    //expand les nodes
    if(!this->isExpanded(_root->index()))
        this->expand(_root->index());
    this->expand(_item->index());
    //---------------------------------------

    delete _buff;
    return _item;
}

//------------------------------------------------------------------------
// ajouter une instance
//------------------------------------------------------------------------
QStandardItem* liste_graphe::ajouter_une_inst(QStandardItem* _item_p,QString& F_name)
{
    QString _f_nom("i:");
    //QFileInfo q_file(F_name());
   //_f_nom.append(q_file.fileName());
    QStandardItem *_item_f=_root->child(_item_p->index().row());

    //creer un node..
    QStandardItem *item=new QStandardItem(_f_nom);
    item->setToolTip(tr("id : ") + F_name);
    item->setIcon(QIcon(":/liste/image/inst.png"));
    item->setEditable(false);
    //cout<<"item:"<<_item_p->index().row()<<endl;
    //cout<<"item:"<<_f_nom.toStdString()<<_item_p->index().row()<<endl;
    _item_f->appendRow(item);
    //item->setAccessibleText(F_name());

    //---------------------------------------
    //selectioner la session creer.
    this->selectionModel()->clearSelection();

    //selectionner l'instance ajoute..
    QItemSelection selection2(item->index(),item->index());
    this->selectionModel()->select(selection2, QItemSelectionModel::Select);

    this->setCurrentIndex(item->index());

    //expand les nodes
    if(!this->isExpanded(_root->index()))
        this->expand(_root->index());

    if(!this->isExpanded(_item_p->index()))
        this->expand(_item_p->index());

    return  item;
}
/*
//------------------------------------------------------------------------
// ajouter une solution
//------------------------------------------------------------------------
QStandardItem* liste_graphe::ajouter_une_sol(QStandardItem* _item_p,solution *_sol)
{
    QString _f_nom("s:");

    QFileInfo q_file(_sol->F_name());
    _f_nom.append(q_file.fileName());

    QStandardItem *_item_f=_root->child(_item_p->index().row());

    //creer un node..
    QStandardItem *item=new QStandardItem(_f_nom);
    item->setToolTip(tr("id : ") + _f_nom);
    item->setIcon(QIcon(":/liste/image/sol.png"));
    item->setEditable(false);
    //cout<<"item:"<<_item_p->index().row()<<endl;
    //cout<<"item:"<<_f_nom.toStdString()<<_item_p->index().row()<<endl;
    _item_f->appendRow(item);
    item->setAccessibleText(_sol->F_name());

    //---------------------------------------
    //selectioner la session creer.
    this->selectionModel()->clearSelection();

    //selectionner l'instance ajoute..
    QItemSelection selection2(item->index(),item->index());
    this->selectionModel()->select(selection2, QItemSelectionModel::Select);

    this->setCurrentIndex(item->index());

    //expand les nodes
    if(!this->isExpanded(_root->index()))
        this->expand(_root->index());

    if(!this->isExpanded(_item_p->index()))
        this->expand(_item_p->index());

    return  item;
}
*/
//--------------------------------------------------------------------
// slot: selecter un item [double click]
//--------------------------------------------------------------------
void liste_graphe::item_selected_slot(QModelIndex _idx)
{
    QStandardItem *_it = _modele->itemFromIndex(_idx);
    //condition d'emettre la signe.
    if(_it->accessibleText().size()>0)
    {
        QModelIndex _idx_file=_idx;
        while(_idx_file.parent()!=_root->index())
           _idx_file=_idx_file.parent();

        QStandardItem *_item_file= _modele->itemFromIndex(_idx_file);

        emit item_selected(_item_file,_it);
    }
}

//--------------------------------------------------------------------
// obtenir la session item a partir du _item_fils donnee...
//--------------------------------------------------------------------
int liste_graphe::get_session_item(QStandardItem *_item_fils,QStandardItem*& _item_session)
{

    //1. verifier le nombre d'intance...
    if(_root->rowCount()<1)
    {
       //QMessageBox::information(this,tr("Erreur : "),tr("Il n'existe pas d'instance.."));
       return -1;
    }

    //3. obtenir la session courante...
    QModelIndex _idx=_item_fils->index();
    if(_idx.parent()==_root->index())//une session
    {
        _item_session= _modele->itemFromIndex(_idx);
    }
    else if(_idx==_root->index())//sessions..
    {
        //_idx_session=_root->index().child(0,0);
        _item_session=_root->child(0,0);
        return 0;
    }
    else
    {//montrer jusqu'au niveau de session/_root
        while(_idx.parent()!=_root->index())
            _idx=_idx.parent();

        _item_session= _modele->itemFromIndex(_idx);
    }

    return 1;
}

