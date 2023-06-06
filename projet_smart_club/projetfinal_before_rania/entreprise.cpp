#include "entreprise.h"
#include <QSqlQuery>
#include <QMessageBox>
#include <connection.h>
#include <QSqlTableModel>
#include <QtDebug>
#include <QObject>
#include <QIntValidator>
#include <QRegExp>

Entreprise::Entreprise()
{
    id_entreprise=0;
    nom_E="";
    ville="";rue="";code_postal=0;
    email="";
}

Entreprise::Entreprise(int id_entreprise,QString nom_E,QString ville,QString rue,int code_postal,QString email,QDate date_colab)
{this->id_entreprise=id_entreprise;this->nom_E=nom_E;this->ville=ville;this->rue=rue;
this->code_postal=code_postal;this->email=email;
this->date_colab=date_colab;
}

int Entreprise::getid_entreprise(){return id_entreprise ;}
QString Entreprise::getnom_E(){return nom_E ;}
QString Entreprise::getville(){return ville;}
QString Entreprise::getrue(){return rue;}
QDate Entreprise::getdate_colab(){return date_colab;}
int Entreprise::getcode_postal(){return code_postal ;}
QString Entreprise::getemail(){return email;}

void Entreprise::setid_entreprise(int id_entreprise){this->id_entreprise=id_entreprise;}
void Entreprise::setnom_E(QString nom_E){this->nom_E=nom_E;}
void Entreprise::setville(QString ville){this->ville=ville;}
void Entreprise::setrue(QString rue){this->rue=rue;}
void Entreprise::setdate_colab(QDate date_colab){this->date_colab=date_colab;}
void Entreprise::setcode_postal(int code_postal){this->code_postal=code_postal;}
void Entreprise::setemail(QString email){this->email=email;}

QSqlTableModel* Entreprise::afficher()
{
QSqlTableModel *model = new QSqlTableModel();
    model->setTable("entreprise");
    model->select();
     model->setEditStrategy(QSqlTableModel::OnManualSubmit);
     model->setHeaderData(0, Qt::Horizontal, QObject::tr("id"));
     model->setHeaderData(1, Qt::Horizontal, QObject::tr("nom"));
     model->setHeaderData(2, Qt::Horizontal, QObject::tr("ville"));
      model->setHeaderData(3, Qt::Horizontal, QObject::tr("rue"));
       model->setHeaderData(4, Qt::Horizontal, QObject::tr("code postal"));
        model->setHeaderData(5, Qt::Horizontal, QObject::tr("email"));
        model->setHeaderData(6, Qt::Horizontal, QObject::tr("date"));
    return model;
}

QStringList Entreprise::ajouter()
{
    QString id_String= QString::number(id_entreprise);
    QString cp= QString::number(code_postal);
    if( id_entreprise==0 ||  nom_E.isEmpty()  || ville.isEmpty() || rue.isEmpty() || code_postal==0 || email.isEmpty() || nom_E.length()<3)
         {{list << "l'ajout a echoue!! car:" ;}
         if(id_entreprise==0){list << "l'id ne doit pas etre nul" ;}
         if(code_postal==0){list << "le code postal ne doit pas etre nul";}
         if(nom_E.isEmpty()){list <<"le nom de l'entreprise ne doit pas etre vide";}
         if(ville.isEmpty()){list <<"la ville ne doit pas etre vide";}
         if(rue.isEmpty()){list <<"le  rue ne doit pas etre vide";}
         if(email.isEmpty()){list <<"l'email ne doit pas etre vide";}
         if(nom_E.length()<3){list <<"le nom de l'entreprise doit contenir au minimum 3 caractères";}
         if(9999<code_postal || 1000>code_postal){list <<"le code postal doit etre un numero entre 10000 et 9999";}
         }
    else{
    QSqlQuery query;
          query.prepare("INSERT INTO entreprise (id_entreprise, nom_E, ville, rue, code_postal, email, date_colab) "
                        "VALUES (:id_entreprise, :nom_E, :ville, :rue, :code_postal, :email, :date_colab)");
          query.bindValue(":id_entreprise", id_String);
          query.bindValue(":nom_E", nom_E);
          query.bindValue(":ville", ville);
          query.bindValue(":rue", rue);
          query.bindValue(":code_postal", cp);
          query.bindValue(":email", email);
          query.bindValue(":date_colab", date_colab);

          if(query.exec()){list <<"Ajouté avec succees";}
          }
    return list;
}
bool Entreprise::supprimer(int id_entreprise)
{
    QSqlQuery query;
            query.prepare("Delete from entreprise where id_entreprise=:id_entreprise");
            query.bindValue(":id_entreprise", id_entreprise);
            return query.exec();
}

QStringList Entreprise::modifier()
{
    QString id_String= QString::number(id_entreprise);
    QString cp= QString::number(code_postal);
    if( id_entreprise==0 ||  nom_E.isEmpty()  || ville.isEmpty() || rue.isEmpty() || code_postal==0 || email.isEmpty() || nom_E.length()<3 ||9999<code_postal || 1000>code_postal)
         {{list << "l'ajout a echoue!! car:" ;}
         if(id_entreprise==0){list << "l'id ne doit pas etre nul" ;}
         if(code_postal==0){list << "le code postal ne doit pas etre nul";}
         if(nom_E.isEmpty()){list <<"le nom de l'entreprise ne doit pas etre vide";}
         if(ville.isEmpty()){list <<"la ville ne doit pas etre vide";}
         if(rue.isEmpty()){list <<"le  rue ne doit pas etre vide";}
         if(email.isEmpty()){list <<"l'email ne doit pas etre vide";}
         if(nom_E.length()<3){list <<"le nom de l'entreprise doit contenir au minimum 3 caractères";}
         if(9999<code_postal || 1000>code_postal){list <<"le code postal doit etre un numero entre 10000 et 9999";}

    }
    else{
  QSqlQuery query;
          query.prepare("Update entreprise set id_entreprise=:id_entreprise, nom_E=:nom_E, ville=:ville, rue=:rue, code_postal=:code_postal, email=:email, date_colab=:date_colab where id_entreprise=:id_entreprise");
          query.bindValue(":id_entreprise", id_String);
          query.bindValue(":nom_E", nom_E);
           query.bindValue(":ville", ville);
           query.bindValue(":rue", rue);
           query.bindValue(":code_postal", cp);
           query.bindValue(":email", email);
            query.bindValue(":date_colab", date_colab);
            if(query.exec()){list <<"modifié avec succees";}
            }
      return list;
}

QSqlQueryModel* Entreprise::charger()
{
        QSqlQueryModel* model=new QSqlQueryModel();
        QSqlQuery* qry=new QSqlQuery();
        qry->prepare("SELECT * FROM ENTREPRISE ");

        /*model->setHeaderData(0, Qt::Horizontal, QObject::tr("id"));
        model->setHeaderData(1, Qt::Horizontal, QObject::tr("nom"));
        model->setHeaderData(2, Qt::Horizontal, QObject::tr("ville"));*/
        qry->exec();

        model->setQuery(*qry);
        return model;
}

QSqlQueryModel* Entreprise::trier()
{
        QSqlQueryModel* model=new QSqlQueryModel();
        QSqlQuery* qry=new QSqlQuery();
        qry->prepare("SELECT * FROM entreprise order by id_entreprise");
        qry->exec();

        model->setQuery(*qry);
        return model;
}

QSqlQueryModel* Entreprise::rechercher(QString val)
{
    QSqlQueryModel* model= new QSqlQueryModel();
    model->setQuery("select * from entreprise where id_entreprise='"+val+"' or nom_E='"+val+"' or ville='"+val+"' ");
    return model;
}

QSqlQuery Entreprise::lister()
{QSqlQuery qry;
    qry.prepare("SELECT nom_E FROM ENTREPRISE  ");
    qry.exec();
    return qry;
}

QSqlQuery Entreprise::exist(int id)
{QString id_e= QString::number(id);

    QSqlQuery qry;
            qry.prepare("select id_entreprise from entreprise where id_entreprise='"+id_e+"'  ");
             qry.bindValue(":id_entreprise",  id_entreprise);
   qry.exec();
    return qry;

}









