#include "adherent.h"
#include <QSqlQuery>
#include <QtDebug>
#include <QDate>

#include <QObject>
#include <QSqlQueryModel>
#include <iostream>
#include <QSqlError>
#include <string>
#include <QSqlQueryModel>
#include <QMessageBox>
#include <QFile>
#include <QTextStream>
//#include "GestionAdherent.h"
#include <QFileDialog>
Adherent::Adherent()
{
id_Adherant=0;
}
Adherent::Adherent(int id_Adherant,QString nom,QString prenom,QString sexe,QString Date_de_Naissance,
                   QString email,int num_tel,QString adresse)
{   this->id_Adherant=id_Adherant;
    this->nom=nom;
    this->prenom=prenom;
    this->sexe=sexe;
    this->Date_de_Naissance=Date_de_Naissance;
    this->email=email;
    this->num_tel=num_tel;
    this->adresse=adresse;}
int Adherent::getid(){return id_Adherant;}
int Adherent::getmailt(){return mailt;}
int Adherent::getnumtelt(){return numtelt;}
int Adherent::getdatet(){return datet;}

QString Adherent::getnom(){return nom;}
QString Adherent::getprenom(){return prenom;}
QString Adherent::getsexe(){return sexe;}
QString Adherent::getdate(){return Date_de_Naissance;}
void Adherent::setid(int id){this->id_Adherant=id;}
void Adherent::setnom(QString nom){this->nom=nom;}
void Adherent::setprenom(QString prenom){this->prenom=prenom;}
void Adherent::setsexe(QString sexe){this->sexe=sexe;}
void Adherent::setdate(QString date){this->Date_de_Naissance=date;}
bool Adherent::ajouter(){

    QSqlQuery query;

       QString id_string =QString::number(id_Adherant);
        QString num_tel_string =QString::number(num_tel);

       query.prepare("INSERT INTO Adherent (id_adherent, nom, prenom,sexe,date_de_Naissance,email,num_tel,adresse) "
                     "VALUES (:id_adherent,:nom,:prenom,:sexe,:date_de_Naissance,:email,:num_tel,:adresse)");
       query.bindValue(":id_adherent", id_string);
       query.bindValue(":nom",nom);
       query.bindValue(":prenom",prenom );
       query.bindValue(":sexe", sexe);
       query.bindValue(":date_de_Naissance",Date_de_Naissance);
       query.bindValue(":email", email);
       query.bindValue(":num_tel", num_tel_string);
       query.bindValue(":adresse", adresse);
       if(id_Adherant==  NULL || nom.isEmpty() || nom.isEmpty() || prenom.isEmpty() ||email.isEmpty() || num_tel==NULL || adresse.isEmpty() )
       {
           QMessageBox::critical(nullptr, QObject::tr("Verification d'ajout"),
                QObject::tr("Erreur champ vid_Categoriee!.\n"
                            "Click Cancel to exit."), QMessageBox::Cancel);
           return false;
       }
       if(/*Date_de_Naissance.year()>2016 ||*/num_tel<10000000 || num_tel>99999999 || email.indexOf('@')==-1||email.indexOf('.')==-1 )
       { if(num_tel<10000000 || num_tel>99999999)
           {
           /*QMessageBox::critical(nullptr, QObject::tr("Verification d'ajout"),
                QObject::tr("numero de telphone non valide !.\n"
                            "Click Cancel to exit."), QMessageBox::Cancel);*/
           numtelt=1;

       }
           /*if(Date_de_Naissance.year()>2016)
           {
               datet=1;

           }*/
       if(email.indexOf('@')==-1||email.indexOf('.')==-1)
       {    mailt=1;
          // ui->email_error->setText("votre email doit contenir @");
           /*QMessageBox::critical(nullptr, QObject::tr("Verification d'ajout"),
                             QObject::tr("email non valide !.\n"
                                         "Click Cancel to exit."), QMessageBox::Cancel);*/

       }
        return false;
}

        qDebug()<<query.lastError().text();
    return query.exec();
}
QSqlQueryModel* Adherent::afficher_adherent()
{
 QSqlQueryModel* model = new QSqlQueryModel();
 model->setQuery("SELECT* FROM Adherent");


    return model;
}
bool Adherent::supprimer_adherent(int Id_Adherent)
{
    QSqlQuery query;

       query.prepare("DELETE from Adherent where Id_Adherent=:Id_Adherent");
       query.bindValue(":Id_Adherent", Id_Adherent);



    return query.exec();

}
bool Adherent::modifier()
{
    QSqlQuery query;
    QString id_string =QString::number(id_Adherant);
    QString num_tel_string =QString::number(num_tel);
    qDebug()<<id_string;
    query.prepare("UPDATE adherent SET id_Adherent='"+id_string+"', nom= '"+nom+"',prenom='"+prenom+"',sexe='"+sexe+"',Date_de_Naissance='"+Date_de_Naissance+"',email='"+email+"',num_tel='"+num_tel_string +"',adresse='"+adresse+"' WHERE id_Adherent='"+id_string+"'");
  //  query.prepare("UPDATE adherent SET id_Adherant='"+id_Adherant+"', nom= :nom,prenom= :prenom,sexe= :sexe,Date_de_Naissance=:Date_de_Naissance,email=:email,num_tel=:numtel,adresse=:adresse WHERE id_Adherent= :id_Adherent");

    query.bindValue(":id_Adherent", id_string);
    query.bindValue(":nom",this->nom);
    query.bindValue(":prenom",this->prenom );
    query.bindValue(":sexe", this->sexe);
    query.bindValue(":Date_de_Naissance",this->Date_de_Naissance);
    query.bindValue(":email", this->email);
    query.bindValue(":num_tel", num_tel_string);
    query.bindValue(":adresse", this->adresse);
    if(!query.exec()){
        qDebug()<< query.lastError().text();
    }
    return query.exec();

}
QSqlQueryModel * Adherent::chercher_adherent(QString nom )
{
    QSqlQueryModel * model= new QSqlQueryModel();
    QSqlQuery query;
    nom='%'+nom+'%';

    //query.prepare("select * from adherent where nom like :nom order by nom");
    query.prepare("select * from adherent where ((id_Adherent || nom || prenom || sexe || Date_de_Naissance ) LIKE '%"+nom+"%')");
    query.addBindValue(nom);
    query.exec();

    model->setQuery(query);
    model->setHeaderData(0,Qt::Horizontal,QObject::tr("id"));
    model->setHeaderData(1,Qt::Horizontal,QObject::tr("nom"));
    model->setHeaderData(2,Qt::Horizontal,QObject::tr("prenom"));
    model->setHeaderData(3,Qt::Horizontal,QObject::tr("sexe"));
    model->setHeaderData(4,Qt::Horizontal,QObject::tr("date"));



        return model;
}
QSqlQueryModel * Adherent::rechercher_com()
 {
     QSqlQueryModel * model=new QSqlQueryModel();
     model->setQuery("SELECT nom FROM Adherent");
     return model;
 }
