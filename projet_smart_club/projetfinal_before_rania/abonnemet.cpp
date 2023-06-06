#include "abonnemet.h"
#include <ctime>
#include<QSqlQuery>
#include<QString>
#include<QDate>
abonnemet::abonnemet()
{
code=0;
nomC="" ;
dateD = "";
dateF = "";
prix=0;
}
abonnemet::abonnemet(int code,QString nomC,QString dateD, QString dateF,float prix)
{
    this->code=code;
    this->nomC=nomC;
    this->dateD=dateD;
    this->dateF=dateF;
    this->prix=prix;
}

QSqlQueryModel* abonnemet::afficher()
{
    QSqlQueryModel* model=new QSqlQueryModel();
    model->setQuery("SELECT * FROM ABONNEMENT");
    model->setHeaderData(0, Qt::Horizontal, QObject::tr("Code"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("Nom Client"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("Date debut"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("Date fin"));
    model->setHeaderData(4, Qt::Horizontal, QObject::tr("Prix"));
    return model;
}

bool abonnemet::ajouter()
{
QSqlQuery query;
  QString code_string=QString::number(code);
  QString prix_string=QString::number(prix);
  query.prepare("insert into abonnement VALUES(:code, :nomC, :dateD, :dateF, :prix)");
  query.bindValue(":code", code_string);
  query.bindValue(":nomC", nomC);
  query.bindValue(":dateD", dateD);
  query.bindValue(":dateF", dateF);
  query.bindValue(":prix", prix_string);
  return query.exec();
}
bool abonnemet::supprimer(int code)
{
    QSqlQuery query;
    QString res =QString::number(code);
    query.prepare("delete from abonnement where code= :code");
    query.bindValue(":code", res);
    return query.exec();
}
bool abonnemet::modifier_abonnement()
{
    QSqlQuery query;
    QString code_string =QString::number(code);
    QString prix_string =QString::number(prix);
    query.prepare("UPDATE abonnement SET code=:code, nomC=:nomC, dateD=:dateD ,dateF=:dateF, prix=:prix where code=:code ");

    query.bindValue(":code", code_string );
    query.bindValue(":nomC", nomC);
    query.bindValue(":dateD", dateD);
    query.bindValue(":dateF", dateF);
    query.bindValue(":prix", prix_string);
    return query.exec();
}
QSqlQueryModel * abonnemet::rechercher(QString res)
{
    QString val=res;
    QSqlQueryModel* model=new QSqlQueryModel();
    model->setQuery("SELECT * FROM finance where id= :id");
    model->setHeaderData(0, Qt::Horizontal, QObject::tr("id"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("type"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("datep"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("prix"));
    model->setHeaderData(4, Qt::Horizontal, QObject::tr("description"));
    return model;
}
