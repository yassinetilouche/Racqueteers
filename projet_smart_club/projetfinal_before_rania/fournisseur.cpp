#include "fournisseur.h"
#include <QSqlQuery>

#include <connection.h>
#include <QSqlTableModel>
#include <QDate>
#include <QtDebug>
#include <QObject>

Fournisseur::Fournisseur()
{
    id_fournisseur=0;telephone=0;facture=0;
    nom="";prenom="";entreprise="";
}

Fournisseur::Fournisseur(int id_fournisseur,int telephone,float facture,QString nom,QString prenom,QString entreprise)
{this->id_fournisseur=id_fournisseur; this->telephone=telephone;this->facture=facture;
this->nom=nom; this->prenom=prenom;this->entreprise=entreprise;}

int Fournisseur::getid_fournisseur(){return id_fournisseur ;}
int Fournisseur::gettelephone(){return telephone ;}
float Fournisseur::getfacture(){return facture ;}
QString Fournisseur::getnom(){return nom ;}
QString Fournisseur::getprenom(){return prenom ;}
QString Fournisseur::getentreprise(){return entreprise ;}


void Fournisseur::setid_fournisseur(int id_fournisseur){this->id_fournisseur=id_fournisseur;}
void Fournisseur::settelephone(int telephone){this->telephone=telephone;}
void Fournisseur::setfacture(float facture){this->facture=facture;}
void Fournisseur::setnom(QString nom){this->nom=nom;}
void Fournisseur::setprenom(QString prenom){this->prenom=prenom;}
void Fournisseur::setentreprise(QString entreprise){this->entreprise=entreprise;}

QSqlTableModel* Fournisseur::afficherf()
{
QSqlTableModel *model = new QSqlTableModel();
    model->setTable("fournisseur");
    model->select();
    model->setHeaderData(0,Qt::Horizontal,QObject::tr("Id"));
    model->setHeaderData(1,Qt::Horizontal,QObject::tr("Tel"));
    model->setHeaderData(2,Qt::Horizontal,QObject::tr("Facture"));
    model->setHeaderData(3,Qt::Horizontal,QObject::tr("Nom"));
    model->setHeaderData(4,Qt::Horizontal,QObject::tr("Prenom"));
    model->setHeaderData(5,Qt::Horizontal,QObject::tr("Entreprise"));
    return model;
}

QStringList Fournisseur::ajouterf()
{
    QString id_String= QString::number(id_fournisseur);
    QString Telephone_String= QString::number(telephone);
    QString facture_String= QString::number(facture);
    if( id_fournisseur==0 || facture==0 || nom.isEmpty() || prenom.isEmpty() || nom.length()<3 || prenom.length()<3 || telephone==0 ||20000000>telephone || 99999999<telephone)
         {{list << "l'ajout a echoue!! car:" ;}
         if(id_fournisseur==0){list << "l'id ne doit pas etre nul" ;}
         if(facture==0){list << "la facture ne doit pas etre nul";}
         if(nom.isEmpty()){list <<"le nom ne doit pas etre vide";}
         if(prenom.isEmpty()){list <<"le prenom ne doit pas etre vide";}
         if(nom.length()<3){list <<"le nom doit depassé 3 caractères";}
         if(prenom.length()<3){list <<"le prenom doit depassé 3 caractères";}
         if(telephone==0){list <<"le telephone ne doit pas etre nul";}
         if(20000000>telephone || 99999999<telephone){list <<"le telephone doit etre un numero entre 20.000.000 et 99.999.999";}
        }
    else{
    QSqlQuery query;
          query.prepare("INSERT INTO fournisseur (id_fournisseur, telephone, facture, nom, prenom, entreprise) "
                        "VALUES (:id_fournisseur, :telephone, :facture, :nom, :prenom, :entreprise)");
          query.bindValue(":id_fournisseur", id_String);
          query.bindValue(":telephone", Telephone_String);
          query.bindValue(":facture", facture_String);
          query.bindValue(":nom", nom);
          query.bindValue(":prenom", prenom);
          query.bindValue(":entreprise", entreprise);

               if(query.exec()){list <<"Ajout avec succes";}
        }
          return list;
}



bool Fournisseur::supprimerf(int id_fournisseur)
{
    QSqlQuery query;
            query.prepare("Delete from fournisseur where id_fournisseur=:id_fournisseur");
            query.bindValue(":id_fournisseur", id_fournisseur);
            return query.exec();
}

QStringList Fournisseur::changerf()
{
    QString id_String= QString::number(id_fournisseur);
    QString telephone_String= QString::number(telephone);
       QString facture_String= QString::number(facture);
       if( id_fournisseur==0 || facture==0 || nom.isEmpty() ||nom.length()<3 || prenom.isEmpty() ||prenom.length()<3 || telephone==0 ||20000000>telephone || 99999999<telephone)
            {{list << "la modification a echoue!! car:" ;}
            if(id_fournisseur==0){list << "l'id ne doit pas etre nul" ;}
            if(facture==0){list << "la facture ne doit pas etre nul";}
            if(nom.isEmpty()){list <<"le nom ne doit pas etre vide";}
            if(prenom.isEmpty()){list <<"le prenom ne doit pas etre vide";}
            if(nom.length()<3){list <<"le nom doit depassé 3 caractères";}
            if(prenom.length()<3){list <<"le prenom doit depassé 3 caractères";}
            if(telephone==0){list <<"le telephone ne doit pas etre nul";}
            if(20000000>telephone || 99999999<telephone){list <<"le telephone doit etre un numero entre 20.000.000 et 99.999.999";}
           }
       else{
  QSqlQuery query;
          query.prepare("Update fournisseur set id_fournisseur=:id_fournisseur, telephone=:telephone, facture=:facture, nom=:nom, prenom=:prenom, entreprise=:entreprise where id_fournisseur=:id_fournisseur");
          query.bindValue(":id_fournisseur", id_String);
          query.bindValue(":telephone", telephone_String);
          query.bindValue(":facture", facture_String);
          query.bindValue(":nom", nom);
          query.bindValue(":prenom", prenom);
          query.bindValue(":entreprise", entreprise);
           if(query.exec()){list <<"Modifier avec succes";}

       }
          return list;
}


QSqlQuery Fournisseur::lister_f()
{QSqlQuery qry;
    qry.prepare("SELECT * FROM Fournisseur");
    qry.exec();
    return qry;
}

QSqlQueryModel* Fournisseur::afficher_f()
{
        QSqlQueryModel* model=new QSqlQueryModel();
        QSqlQuery* qry=new QSqlQuery();
        qry->prepare("SELECT * FROM FOURNISSEUR ");
        qry->exec();

        model->setQuery(*qry);
        return model;
}

QSqlQuery Fournisseur::lister()
{QSqlQuery qry;
    qry.prepare("SELECT id_fournisseur FROM fournisseur  ");
    qry.exec();
    return qry;
}
