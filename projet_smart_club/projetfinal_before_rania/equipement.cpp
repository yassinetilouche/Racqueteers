#include "equipement.h"
#include <QSqlQuery>

#include <connection.h>
#include <QSqlTableModel>
#include <QMessageBox>
#include <QtDebug>
#include <QObject>

Equipement::Equipement()
{
    id_equipement=0;nombre=0;prix=0;
    etat="";type="";disponibilite="";
}

Equipement::Equipement(int id_equipement,QString etat,int nombre,QString type,float prix,QString disponibilite)
{this->id_equipement=id_equipement; this->etat=etat;
this->nombre=nombre;this->type=type;this->prix=prix; this->disponibilite=disponibilite;}

int Equipement::getid_equipement(){return id_equipement ;}
int Equipement::getnombre(){return nombre ;}
QString Equipement::getetat(){return etat;}
QString Equipement::gettype(){return type;}
float Equipement::getprix(){return prix;}
QString Equipement::getdisponibilite(){return disponibilite;}

void Equipement::setid_equipement(int id_equipement){this->id_equipement=id_equipement;}
void Equipement::setnombre(int nombre){this->nombre=nombre;}
void Equipement::setetat(QString etat){this->etat=etat;}
void Equipement::settype(QString type){this->type=type;}
void Equipement::setprix(float prix){this->prix=prix;}
void Equipement::setdisponibilite(QString disponibilite){this->disponibilite=disponibilite;}

QSqlTableModel* Equipement::afficher()
{
QSqlTableModel *model = new QSqlTableModel();
    model->setTable("equipement");
    model->select();
     model->setEditStrategy(QSqlTableModel::OnManualSubmit);
     model->setHeaderData(0, Qt::Horizontal, QObject::tr("id"));
     model->setHeaderData(1, Qt::Horizontal, QObject::tr("etat"));
     model->setHeaderData(2, Qt::Horizontal, QObject::tr("nombre"));
     model->setHeaderData(3, Qt::Horizontal, QObject::tr("type"));
     model->setHeaderData(4, Qt::Horizontal, QObject::tr("prix"));
     model->setHeaderData(4, Qt::Horizontal, QObject::tr("disponibilite"));
   /* model->database().transaction();
    if (model->submitAll()) {
        model->database().commit();}*/
    return model;
}

QStringList Equipement::ajouter()
{
    QString id_String= QString::number(id_equipement);
    QString nombre_String= QString::number(nombre);
    QString prix_String= QString::number(prix);
    if( id_equipement==0 ||  nombre==0  || prix==0)
         {{list << "l'ajout a echoue!! car:" ;}
         if(id_equipement==0){list << "l'id ne doit pas etre nul" ;}
         if(nombre==0){list << "le nombre ne doit pas inferieur a 0";}
         if(prix==0){list <<"le prix ne doit pas inferieur a 0 DT";}
         }
    else{
    QSqlQuery query;
          query.prepare("INSERT INTO equipement (id_equipement, etat, nombre, type, prix, disponibilite) "
                        "VALUES (:id_equipement, :etat, :nombre, :type, :prix, :disponibilite)");
          query.bindValue(":id_equipement", id_String);
          query.bindValue(":etat", etat);
          query.bindValue(":nombre", nombre_String);
          query.bindValue(":type", type);
          query.bindValue(":prix", prix_String);
          query.bindValue(":disponibilite", disponibilite);

          if(query.exec()){list <<"l'ajout est effectué avec succés";}
    }
          return list;
}

bool Equipement::supprimer(int id_equipement)
{
    QSqlQuery query;
            query.prepare("Delete from equipement where id_equipement=:id_equipement");
            query.bindValue(":id_equipement", id_equipement);
            return query.exec();
}

QStringList Equipement::changer()
{
    QString id_String= QString::number(id_equipement);
    QString nombre_String= QString::number(nombre);
       QString prix_String= QString::number(prix);
       if( id_equipement==0 ||  nombre==0  || prix==0)
            {{list << "la modification a echoue!! car:" ;}
            if(id_equipement==0){list << "l'id ne doit pas etre nul" ;}
            if(nombre==0){list << "le nombre ne doit pas inferieur a 0";}
            if(prix==0){list <<"le prix ne doit pas inferieur a 0 DT";}
            }
       else{
  QSqlQuery query;
          query.prepare("Update equipement set id_equipement=:id_equipement, etat=:etat, nombre=:nombre, type=:type, prix=:prix, disponibilite=:disponibilite where id_equipement=:id_equipement");
          query.bindValue(":id_equipement", id_String);
          query.bindValue(":etat", etat);
           query.bindValue(":nombre", nombre_String);
           query.bindValue(":type", type);
            query.bindValue(":prix", prix_String);
            query.bindValue(":disponibilite", disponibilite);

           if(query.exec()){list <<"la modification est effectué avec succés";}
           }
            return list;
}

QSqlQuery Equipement::lister()
{QSqlQuery qry;
    qry.prepare("SELECT * FROM EQUIPEMENT ");
    qry.exec();
    return qry;
}

QSqlQueryModel* Equipement::charger()
{
        QSqlQueryModel* model=new QSqlQueryModel();
        QSqlQuery* qry=new QSqlQuery();
        qry->prepare("SELECT * FROM EQUIPEMENT ");
        qry->exec();

        model->setQuery(*qry);
        return model;
}

QSqlQueryModel* Equipement::trier()
{
        QSqlQueryModel* model=new QSqlQueryModel();
        QSqlQuery* qry=new QSqlQuery();
        qry->prepare("SELECT * FROM EQUIPEMENT order by id_equipement");
        qry->exec();

        model->setQuery(*qry);
        return model;
}

QSqlQueryModel* Equipement::rechercher(QString eta)
{   //int eta_int=eta.toInt();
    QSqlQueryModel* model= new QSqlQueryModel();
    model->setQuery("select * from equipement where etat='"+eta+"' or type='"+eta+"' ");
    return model;
}

int Equipement::recherche(QString eta,QString typ)
{ QSqlQuery q;
    q.prepare("select nombre from equipement where etat='"+eta+"' and type='"+typ+"' ");
    q.exec();
    int a=0;
    while(q.next())
    {a= q.value(0).toInt()+a;
    }
    return a;
}


/*bool Equipement::existe(int id_equipement)
{
    QSqlQuery q;
    q.prepare("Select id_equipement from equipement where id_equipement=:id_equipement");
    q.bindValue(":id_equipement", id_equipement);
    return (q.first());
}*/

QSqlQuery Equipement::lister(QString eta)
{QSqlQuery qry;
    qry.prepare("SELECT id_equipement FROM equipement where disponibilite='"+eta+"'");
    qry.exec();
    return qry;
}



