#include "login.h"
#include<iostream>
#include<QSqlQueryModel>
#include <QObject>
#include <QSqlQuery>
#include <QtDebug>
#include<QMessageBox>
login::login()
{
nom="";
prenom="";
age=0;
username="";
mdp="";
telephone=0;
}
login::login(QString a,QString b,int c,QString d,QString e,int f)
{
    nom=a;
    prenom=b;
    age=c;
    username=d;
    mdp=e;
    telephone=f;
}
bool login::ajouter()
{
    QSqlQuery query;
    QString age_string = QString::number(age);
    QString telephone_string = QString::number(telephone);
    query.prepare(" insert into login values (:nom, :prenom, :age, :username, :mdp, :telephone)");
    query.bindValue(":nom", nom );
    query.bindValue(":prenom", prenom );
    query.bindValue(":age", age_string );
    query.bindValue(":username", username );
    query.bindValue(":mdp", mdp);
    query.bindValue(":telephone", telephone_string );
    return query.exec();
}
