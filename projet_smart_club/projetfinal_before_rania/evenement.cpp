#include "evenement.h"
#include <QSqlQuery>
#include <QtDebug>
#include <QDate>
#include <QTime>
#include <QObject>
#include <QPrinter>
//#include <QPdfWriter>
//#include <QPrintDialog>
#include <QPainter>
#include "QPdfWriter"
#include "QDesktopServices"
#include "QtPrintSupport/QPrinter"
#include <QMessageBox>
#include <QVariant>

Evenement::Evenement()
{
    id = 0;
    type = "";
   /* date_debut = "";
    heure_debut = "";*/
    nombrePlace = 0;
    lieu = "";
}

Evenement::Evenement(int id,QString type,QString date,QString heure,int nbre,QString lieu)
{
    this->id = id;
    this->type = type;
    this->date_debut = date;
    this->heure_debut = heure;
    this->nombrePlace = nbre;
    this->lieu = lieu;
}
int Evenement::getId()
{
    return this->id;
}
QString Evenement::getType()
{
    return this->type;
}
QString Evenement::getDate()
{
    return this->date_debut;
}
QString Evenement::getHeure()
{
    return this->heure_debut;
}
int Evenement::getNbr()
{
    return this->nombrePlace;
}
QString Evenement::getLieu()
{
    return this->lieu;
}
void Evenement::setType(QString type)
{
    this->type = type;
}
bool Evenement::ajouter()
{
    QString id_string = QString::number(id);
    QString place = QString::number(nombrePlace);

    QSqlQuery query;
    query.prepare("INSERT INTO evenements (ID, TYPE, DATE_D,HEURE_D,PLACE,LIEU) " "VALUES (:id, :type, :date, :heure, :place, :lieu)");
    query.bindValue(":id", id_string);
    query.bindValue(":type", type);
    query.bindValue(":date", date_debut);
    query.bindValue(":heure", heure_debut);
    query.bindValue(":place", place);
    query.bindValue(":lieu", lieu);

    return query.exec();

}

QSqlQueryModel* Evenement::afficher()
{
    QSqlQueryModel* model = new QSqlQueryModel();
    model->setQuery("SELECT * FROM EVENEMENTS");
    model->setHeaderData(0, Qt::Horizontal, QObject::tr("Identifiant"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("Type"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("Date de debut"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("Heure de debut"));
    model->setHeaderData(4, Qt::Horizontal, QObject::tr("Nombre des places"));
    model->setHeaderData(5, Qt::Horizontal, QObject::tr("Lieu"));

    return model;
}

bool Evenement::supprimer(int id)
{
    QSqlQuery query;
    query.prepare("Delete from evenements where ID = :id ");
    query.bindValue(":id",id);
    return query.exec();
}

bool Evenement::modifier(int id)
{
    QSqlQuery query;
    query.prepare("UPDATE evenements set TYPE=:type,DATE_D=:date,HEURE_D = :heure, PLACE = :place, LIEU =:lieu where ID=:id ");
    query.bindValue(":id",id);
    query.bindValue(":type",type);
    query.bindValue(":date",date_debut);
    query.bindValue(":heure",heure_debut);
    query.bindValue(":place",nombrePlace);
    query.bindValue(":lieu",lieu);

    return query.exec();
}

QSqlQueryModel* Evenement::rechercher(QString s)
{
    QSqlQueryModel* model = new QSqlQueryModel();

    //model->setQuery("select * from evenenments where ID = " + s + " or TYPE = '" + s + "' or DATE_D = '" + s +"' or HEURE_D = '" + s + "' or PLACE = " + s + " or LIEU = '" + s + "'");
    //model->setQuery("select * from evenements where id = " + s);
    model->setQuery("select * from evenements where id = "+ s +" or type = '"+ s +"' or date_d = '"+ s +"' or heure_d = '"+ s +"' or lieu = '"+ s +"' or place = '"+ s +"'");
    //model->setQuery("select * from evenements where ((id || type || date_d || heure_d || lieu || place) like %" + s + "%");
    model->setHeaderData(0, Qt::Horizontal, QObject::tr("Identifiant"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("Type"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("Date de debut"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("Heure de debut"));
    model->setHeaderData(4, Qt::Horizontal, QObject::tr("Nombre des places"));
    model->setHeaderData(5, Qt::Horizontal, QObject::tr("Lieu"));

    return model;
}

QSqlQueryModel* Evenement::triAsc()
{
    QSqlQueryModel* model = new QSqlQueryModel();

    model->setQuery("select * from evenements order by ID ASC");
    model->setHeaderData(0, Qt::Horizontal, QObject::tr("Identifiant"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("Type"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("Date de debut"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("Heure de debut"));
    model->setHeaderData(4, Qt::Horizontal, QObject::tr("Nombre des places"));
    model->setHeaderData(5, Qt::Horizontal, QObject::tr("Lieu"));

    return model;
}

QSqlQueryModel* Evenement::triDesc()
{
    QSqlQueryModel* model = new QSqlQueryModel();

    model->setQuery("select * from evenements order by ID desc");
    model->setHeaderData(0, Qt::Horizontal, QObject::tr("Identifiant"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("Type"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("Date de debut"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("Heure de debut"));
    model->setHeaderData(4, Qt::Horizontal, QObject::tr("Nombre des places"));
    model->setHeaderData(5, Qt::Horizontal, QObject::tr("Lieu"));

    return model;
}

void Evenement::pdf(QString filename)
{
    /*QPrinter printer;
          printer.setOutputFormat(QPrinter::PdfFormat);
          printer.setOutputFileName(filename);
          QPainter painter;
          if (! painter.begin(&printer)) { // failed to open file
              qWarning("failed to open file, is it writable?");
              return ;
          }
          painter.setPen(Qt::blue);
          painter.setFont(QFont("Arial", 30));
          painter.drawText(100, 200, "Evenement :");

          painter.setPen(Qt::black);
          painter.setFont(QFont("Arial", 9));
          painter.drawText(100,200,"Id :" + ui->);

          painter.end();*/
    QPdfWriter pdf(filename);
    QPainter painter(&pdf);
    int i = 4000;
    painter.setPen(Qt::blue);
    painter.setFont(QFont("Arial", 30));
    painter.drawText(2300,1200,"Liste Des Evenements");
    painter.setPen(Qt::black);
    painter.setFont(QFont("Arial", 50));
                                 // painter.drawText(1100,2000,afficheDC);
    //painter.drawRect(1500,200,7300,2600);
                                  //painter.drawPixmap(QRect(7600,70,2000,2600),QPixmap("C:/Users/RH/Desktop/projecpp/image/logopdf.png"));
    painter.drawRect(0,3000,9600,500);
    painter.setFont(QFont("Arial", 9));
    painter.drawText(300,3300,"Identification :");
    painter.drawText(2300,3300,"Type :");
    painter.drawText(4300,3300,"Date de debut :");
    painter.drawText(6300,3300,"heure debut :");
    painter.drawText(8300,3300,"Nombre des place :");
    painter.drawText(10300,3300,"Lieu :");



    QSqlQuery query;
    query.prepare("select * from evenements");
    query.exec();
    while (query.next())
    {
        painter.drawText(300,i,query.value(0).toString());
        painter.drawText(2300,i,query.value(1).toString());
        painter.drawText(4300,i,query.value(2).toString());
        painter.drawText(6300,i,query.value(3).toString());
        painter.drawText(8300,i,query.value(4).toString());
        painter.drawText(10300,i,query.value(5).toString());



        i = i +500;
     }
      /*int reponse = QMessageBox::question(this, "Génerer PDF", "<PDF Enregistré>...Vous Voulez Affichez Le PDF ?", QMessageBox::Yes |  QMessageBox::No);
       if (reponse == QMessageBox::Yes)
       {

         painter.end();
       }
       if (reponse == QMessageBox::No)
       {
            painter.end();
       }*/
    painter.end();
}

int Evenement::number()
{
    QVariant n;
    QSqlQuery qry;
    qry.prepare("SELECT count(*) as nombre FROM evenements");
    qry.exec();

    while(qry.next())
    n = qry.value("nombre");

    return n.toInt();


}

QSqlQueryModel * Evenement::rechercherEvenement()
{
    QSqlQueryModel * model=new QSqlQueryModel();
    model->setQuery("SELECT ID, TYPE, DATE_D, HEURE_D, PLACE, LIEU FROM evenements");
    return model;
}

QVector<double> Evenement::data_from_Base(int m, int y)
{
    QVector<double> data;
    QSqlQuery qry;
    QString m1;
    QString y1;

    if((y % 100)< 10)
        y1 = "0" + QString::number(y % 100);
    else
        y1 = QString::number(y % 100);

    for(int i = m;i < (m+3); i++)
    {
        if(i < 10)
            m1 = "0" + QString::number(i);
        else
            m1 = QString::number(i);
        qry.prepare("select count(date_d) as data from evenements where date_d like '__/" + m1 +"/" + y1 +"'");
        //qDebug()<< "select count(date_d) as data from evenements where date_d like '__/" + m1 +"/__'";
        qry.exec();

        while(qry.next()){
            //qDebug() <<qry.value("data");
            data.push_back(qry.value("data").toDouble());
        }
    }

    /*for(QVector<int>::iterator it = data.begin(); it != data.end(); ++it)
    {
        qDebug() <<' '<< *it;
    }*/

    return data;

}
