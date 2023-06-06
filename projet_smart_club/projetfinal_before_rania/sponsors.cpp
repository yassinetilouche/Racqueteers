#include "sponsors.h"
#include <QSqlQuery>
#include <QtDebug>
//#include <QDate>
//#include <QTime>
//#include <QObject>
//#include <QPrinter>
//#include <QPdfWriter>
//#include <QPrintDialog>
//#include <QPainter>
//#include "QPdfWriter"
//#include "QDesktopServices"
//#include "QtPrintSupport/QPrinter"
#include <QMessageBox>

Sponsors::Sponsors()
{
    id = 0;
    tel = 0;
    nom_e = "";
    email = "";
    type = "";
    materiels = "";
}

Sponsors::Sponsors(int id, int tel, QString nom_e, QString email, QString type, QString materiels)
{
    this->id = id;
    this->tel = tel;
    this->nom_e = nom_e;
    this->email = email;
    this->type = type;
    this->materiels = materiels;
}

bool Sponsors::ajouter()
{
    QString id_string = QString::number(this->id);
    QString tele = QString::number(this->tel);

    QSqlQuery query;
    query.prepare("INSERT INTO sponsors (ID, TELEPHONE, NOM_ENTREPRISE,EMAIL,TYPE,MATERIELS_FOURNIS) " "VALUES (:id, :tel, :nom, :email, :type, :mat)");
    query.bindValue(":id", id_string);
    query.bindValue(":tel", tele);
    query.bindValue(":nom", this->nom_e);
    query.bindValue(":email", this->email);
    query.bindValue(":type", this->type);
    query.bindValue(":mat", this->materiels);

    return query.exec();
}

bool Sponsors::supprimer(int id)
{
    QSqlQuery query;
    query.prepare("Delete from sponsors where ID = :id ");
    query.bindValue(":id",id);
    return query.exec();
}

QSqlQueryModel* Sponsors::afficher()
{
    QSqlQueryModel* model = new QSqlQueryModel();
    model->setQuery("SELECT * FROM sponsors");
    model->setHeaderData(0, Qt::Horizontal, QObject::tr("Identifiant"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("Telephone"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("Nom de l'entreprise"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("Email"));
    model->setHeaderData(4, Qt::Horizontal, QObject::tr("Type"));
    model->setHeaderData(5, Qt::Horizontal, QObject::tr("Materiel fournis"));

    return model;
}

bool Sponsors::modifier(int id1)
{
    QSqlQuery query;
    query.prepare("UPDATE sponsors set telephone=:tel,nom_entreprise=:nom,email = :email, type = :type, materiels_fournis =:mat where ID=:id ");
    query.bindValue(":id",id1);
    query.bindValue(":tel",this->tel);
    query.bindValue(":nom",this->nom_e);
    query.bindValue(":email",this->email);
    query.bindValue(":type",this->type);
    query.bindValue(":mat",this->materiels);

    return query.exec();
}

QSqlQueryModel* Sponsors::rechercher(QString s)
{
    QSqlQueryModel* model = new QSqlQueryModel();

    //model->setQuery("select * from evenenments where ID = " + s + " or TYPE = '" + s + "' or DATE_D = '" + s +"' or HEURE_D = '" + s + "' or PLACE = " + s + " or LIEU = '" + s + "'");
    //model->setQuery("select * from evenements where id = " + s);
    model->setQuery("select * from sponsors where id = "+ s +" or nom_entreprise = '"+ s +"' or telephone = "+ s +" or email = '"+ s +"' or type = '"+ s +"' or materiels_fournis = '"+ s +"'");
    model->setHeaderData(0, Qt::Horizontal, QObject::tr("Identifiant"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("Telephone"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("Nom de l'entreprise"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("Email"));
    model->setHeaderData(4, Qt::Horizontal, QObject::tr("Type"));
    model->setHeaderData(5, Qt::Horizontal, QObject::tr("Materiel fournis"));

    return model;
}

QSqlQueryModel* Sponsors::triAsc()
{
    QSqlQueryModel* model = new QSqlQueryModel();

    model->setQuery("select * from sponsors order by ID ASC");
    model->setHeaderData(0, Qt::Horizontal, QObject::tr("Identifiant"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("Telephone"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("Nom de l'entreprise"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("Email"));
    model->setHeaderData(4, Qt::Horizontal, QObject::tr("Type"));
    model->setHeaderData(5, Qt::Horizontal, QObject::tr("Materiel fournis"));

    return model;
}

QString Sponsors::getEmail()
{
    return this->email;
}

QString Sponsors::getType()
{
    return this->type;
}

QString Sponsors::getMateriels()
{
    return this->materiels;
}

QSqlQueryModel* Sponsors::triDesc()
{
    QSqlQueryModel* model = new QSqlQueryModel();

    model->setQuery("select * from sponsors order by ID desc");
    model->setHeaderData(0, Qt::Horizontal, QObject::tr("Identifiant"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("Telephone"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("Nom de l'entreprise"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("Email"));
    model->setHeaderData(4, Qt::Horizontal, QObject::tr("Type"));
    model->setHeaderData(5, Qt::Horizontal, QObject::tr("Materiel fournis"));

    return model;
}
