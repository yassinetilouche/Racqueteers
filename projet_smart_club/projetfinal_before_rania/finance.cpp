#include <QSqlQuery>
#include <QtDebug>
#include<iostream>
#include<QSqlQueryModel>
#include <QObject>
#include "finance.h"
#include<vector>
#include<QMessageBox>
using namespace std;
finance::finance()
{
id=0; type=""; date=""; description="";prix=0;
}
finance::finance(int id,QString type,QString date,QString description,float prix)
{
    this->id=id;
    this->type=type;
    this->date=date;
    this->description=description;
    this->prix=prix;
}
int finance::getId(){return id;}
QString finance::getType(){return type;}
QString finance::getDate(){return date;}
QString finance::getDescription(){return description;}
float finance::getPrix(){return prix;}
void finance::setId(int id){this->id=id;}
void finance::setType(QString type){this->type=type;}
void finance::setDate(QString date){this->date=date;}
void finance::setDescription(QString description){this->description=description;}
void finance::setPrix(float prix){this->prix=prix;}
bool finance::ajouter()
{

    QSqlQuery query;
    QString idd = QString::number(id);
    QString prixx = QString::number(prix);
    query.prepare("insert into finance VALUES (:id, :type, :date, :prix, :description)");
    query.bindValue(":id", idd);
    query.bindValue(":type", type);
    query.bindValue(":date", date);
    query.bindValue(":prix", prixx);
    query.bindValue(":description", description);
   return query.exec();
}
QSqlQueryModel * finance::afficher()

{
QSqlQueryModel* model=new QSqlQueryModel();
model->setQuery("SELECT * FROM finance");
model->setHeaderData(0, Qt::Horizontal, QObject::tr("id"));
model->setHeaderData(1, Qt::Horizontal, QObject::tr("type"));
model->setHeaderData(2, Qt::Horizontal, QObject::tr("date"));
model->setHeaderData(3, Qt::Horizontal, QObject::tr("prix"));
model->setHeaderData(4, Qt::Horizontal, QObject::tr("description"));
return model;
}
bool finance::supprimer(int id)
{
    QSqlQuery query;
    QString res =QString::number(id);
    query.prepare("delete from finance where id= :id");
    query.bindValue(":id",res);
    return query.exec();
}
bool finance::modifier_finance()
{
    QSqlQuery query;
    QString id_string =QString::number(id);
    QString prix_string =QString::number(prix);
    query.prepare("UPDATE finance SET id='"+id_string+"', type='"+type+"', datep='"+date+"' ,prix='"+prix_string+"', description='"+description+"'where id='"+id_string+"' ");
    query.bindValue(":id",id_string );
    query.bindValue(":type", type);
    query.bindValue(":date", date);
    query.bindValue(":prix", prix_string);
    query.bindValue("description", description);
    return query.exec();

}
QSqlQueryModel * finance::rechercher(QString type)
{
    QSqlQuery query;
        QSqlQueryModel* model=new QSqlQueryModel();
        model->setQuery("SELECT * FROM finance where type='"+type+"' ");
        model->setHeaderData(0, Qt::Horizontal, QObject::tr("id"));
        model->setHeaderData(1, Qt::Horizontal, QObject::tr("type"));
        model->setHeaderData(2, Qt::Horizontal, QObject::tr("datep"));
        model->setHeaderData(3, Qt::Horizontal, QObject::tr("prix"));
        model->setHeaderData(4, Qt::Horizontal, QObject::tr("description"));
        query.bindValue(":type",type );
        return model;
}
QSqlQueryModel * finance::trieFinanace()
{
    QSqlQueryModel* model=new QSqlQueryModel();
    model->setQuery("SELECT * FROM finance order by id");
    model->setHeaderData(0, Qt::Horizontal, QObject::tr("id"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("type"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("date"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("prix"));
    model->setHeaderData(4, Qt::Horizontal, QObject::tr("description"));
    return model;
}
