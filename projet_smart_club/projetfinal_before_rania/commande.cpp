#include "commande.h"

#include <QSqlQuery>
#include <QMessageBox>
#include <connection.h>
#include <QSqlTableModel>
#include <QtDebug>
#include <QObject>
#include <QIntValidator>
#include <QRegExp>

commande::commande()
{
    id_commande=0;
    id_f=0;
    type_commande="";
    id_eq=0;
}

commande::commande(int id_commande,QDate date_commande,int id_f,QString type_commande,int id_eq)
{this->id_commande=id_commande;this->date_commande=date_commande;this->id_f=id_f;this->type_commande=type_commande;
this->id_eq=id_eq;
}

int commande::getid_commande(){return id_commande ;}
QDate commande::getdate_commande(){return date_commande ;}
int commande::getid_f(){return id_f;}
QString commande::gettype_commande(){return type_commande;}
int commande::getid_eq(){return id_eq;}


void commande::setid_commande(int id_commande){this->id_commande=id_commande;}
void commande::setdate_commande(QDate date_commande){this->date_commande=date_commande;}
void commande::setid_f(int id_f){this->id_f=id_f;}
void commande::settype_commande(QString type_commande){this->type_commande=type_commande;}
void commande::setid_eq(int id_eq){this->id_eq=id_eq;}


QSqlTableModel* commande::afficher()
{
QSqlTableModel *model = new QSqlTableModel();
    model->setTable("commande");
    model->select();
     model->setEditStrategy(QSqlTableModel::OnManualSubmit);
     model->setHeaderData(0, Qt::Horizontal, QObject::tr("id"));
     model->setHeaderData(1, Qt::Horizontal, QObject::tr("date"));
     model->setHeaderData(2, Qt::Horizontal, QObject::tr("id_fournisseur"));
      model->setHeaderData(3, Qt::Horizontal, QObject::tr("type"));
       model->setHeaderData(4, Qt::Horizontal, QObject::tr("id_equipement"));
    return model;
}

QStringList commande::ajouter()
{
    QString co= QString::number(id_commande);
    QString eq= QString::number(id_eq);
    QString f= QString::number(id_f);

    if( id_commande==0 || type_commande.isEmpty() )
         {{list << "l'ajout a echoue!! car:" ;}
         if(id_commande==0){list << "l'id ne doit pas etre nul" ;}
         if(type_commande.isEmpty()){list << "le type de commande ne doit pas etre nul";}
         }
    else{
    QSqlQuery query;
          query.prepare("INSERT INTO commande (id_commande, date_commande, id_f, type_commande, id_eq) "
                        "VALUES (:id_commande, :date_commande, :id_f, :type_commande, :id_eq)");
          query.bindValue(":id_commande", co);
          query.bindValue(":date_commande", date_commande);
          query.bindValue(":id_f", f);
          query.bindValue(":type_commande", type_commande);
          query.bindValue(":id_eq", eq);

          if(query.exec()){list <<"Ajouté avec succees";}
          }
    return list;
}
bool commande::supprimer(int id_commande)
{
    QSqlQuery query;
            query.prepare("Delete from commande where id_commande=:id_commande");
            query.bindValue(":id_commande", id_commande);
            return query.exec();
}

QStringList commande::modifier()
{
    QString co= QString::number(id_commande);
    QString eq= QString::number(id_eq);
    QString f= QString::number(id_f);
    if( id_commande==0 || type_commande.isEmpty() )
         {{list << "l'ajout a echoue!! car:" ;}
         if(id_commande==0){list << "l'id ne doit pas etre nul" ;}
         if(type_commande.isEmpty()){list << "le type de commande ne doit pas etre nul";}
         }
    else{
  QSqlQuery query;
        query.prepare("UPDATE commande (id_commande, date_commande, id_f, type_commande, id_eq) "
                        "VALUES (:id_commande, :date_commande, :id_f, :type_commande, :id_eq)");
          query.bindValue(":id_commande", co);
          query.bindValue(":date_commande", date_commande);
          query.bindValue(":id_f", f);
          query.bindValue(":type_commande", type_commande);
          query.bindValue(":id_eq", eq);
            if(query.exec()){list <<"modifié avec succees";}
            }
      return list;
}

QSqlQueryModel* commande::charger()
{
        QSqlQueryModel* model=new QSqlQueryModel();
        QSqlQuery* qry=new QSqlQuery();
        qry->prepare("SELECT * FROM commande ");

        /*model->setHeaderData(0, Qt::Horizontal, QObject::tr("id"));
        model->setHeaderData(1, Qt::Horizontal, QObject::tr("nom"));
        model->setHeaderData(2, Qt::Horizontal, QObject::tr("ville"));*/
        qry->exec();

        model->setQuery(*qry);
        return model;
}

QSqlQueryModel* commande::trier()
{
        QSqlQueryModel* model=new QSqlQueryModel();
        QSqlQuery* qry=new QSqlQuery();
        qry->prepare("SELECT * FROM commande order by id_commande");
        qry->exec();

        model->setQuery(*qry);
        return model;
}

QSqlQueryModel* commande::rechercher(QString val)
{
    QSqlQueryModel* model= new QSqlQueryModel();
    model->setQuery("select * from commande where id_commande='"+val+"'  ");
    return model;
}
/*
QSqlQuery commande::lister()
{QSqlQuery qry;
    qry.prepare("SELECT nom_E FROM commande  ");
    qry.exec();
    return qry;
}*/


