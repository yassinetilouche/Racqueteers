#include "employee.h"
#include <QSqlQuery>
#include <QtDebug>
#include <QDate>
#include <QObject>
#include <QMessageBox>
#include <QSqlError>
#include "mainwindow.h"

Employee::Employee()
{
id=0;
}
Employee::Employee(int id,  QString lastname ,QString name , QString email,int phone , QString address,QDate birthdate,QDate entrydate,QString poste )
{
   this->id=id;
   this->lastname=lastname;
   this->name=name;
   this->email=email;
   this->phone=phone;
   this->address=address;
   this->birthdate=birthdate;
   this->entrydate=entrydate;
    this->poste=poste;

};
int Employee::getid(){return id ;}
int Employee::getphone(){return phone;}
QString Employee::getname(){return name;}
QString Employee::getlastname(){return lastname;}
QString Employee::getemail(){return email;}
QString Employee::getaddress(){return address;}
QDate Employee::getbirthdate(){return birthdate;}
QDate Employee::getentrydate(){return entrydate;}
QString Employee::getposte(){return poste;}
void Employee::setid(int id){    this->id=id;}
void Employee::setphone(int phone){    this->phone=phone;}
void Employee::setname(QString name){    this->name=name;}
void Employee::setlastname(QString lastname){    this->lastname=lastname;}
void Employee::setemail(QString email){    this->email=email;}
void Employee::setaddress(QString address){    this->address=address;}
void Employee::setbirthdate(QDate birthdate){    this->birthdate=birthdate;}
void Employee::setentrydate(QDate entrydate){    this->entrydate=entrydate;}
void Employee::setposte(QString poste){    this->poste=poste;}

QString Employee::ajouter(){
    QString test="";
    QSqlQuery query;
       QString id_string =QString::number(id);
       QString phone_string =QString::number(phone);


       query.prepare("INSERT INTO employee (id, lastname, name,email,phone,address,birthdate,entrydate,poste) "
                     "VALUES (:id, :lastname, :name,:email,:phone,:address,:birthdate,:entrydate,:poste)");
       query.bindValue(":id", id_string);
       query.bindValue(":lastname", lastname);
       query.bindValue(":name", name);
       query.bindValue(":email", email);
       query.bindValue(":phone", phone_string);
       query.bindValue(":address", address);
       query.bindValue(":birthdate", birthdate);
       query.bindValue(":entrydate", entrydate);
       query.bindValue(":poste", poste);
       if(id==  NULL   )

            {

                 test=test+"2";
             }
       if(lastname.isEmpty()  )

            {

                 test=test+"3";
             }
       if(name.isEmpty()  )

            {


                 test=test+"4";
             }
       if(address.isEmpty()  )

            {

                 test=test+"5";
             }

       if(phone==  NULL  )

            {

                 test=test+"6";
             }
             if(phone<1000000 || phone>9999999 )
             {

                 test=test+"7";

             }
             if(email.indexOf('@')==-1||email.indexOf('.')==-1||email.isEmpty())
             {

                 test=test+"8";
             }
             if(poste.isEmpty()  )

                  {
                       test=test+"9";
             }

            if (test=="")
            {
                query.exec();
            }

              qDebug()<<query.lastError().text();

            qDebug() <<test;

    return test; }





/*bool Employee::ajouter(){

    QSqlQuery query;
       QString id_string =QString::number(id);
       QString phone_string =QString::number(phone);


       query.prepare("INSERT INTO employee (id, lastname, name,email,phone,address,birthdate,entrydate,poste) "
                     "VALUES (:id, :lastname, :name,:email,:phone,:address,:birthdate,:entrydate,:poste)");
       query.bindValue(":id", id_string);
       query.bindValue(":lastname", lastname);
       query.bindValue(":name", name);
       query.bindValue(":email", email);
       query.bindValue(":phone", phone_string);
       query.bindValue(":address", address);
       query.bindValue(":birthdate", birthdate);
       query.bindValue(":entrydate", entrydate);
       query.bindValue(":poste", poste);
       if(id==  NULL   )

            {
                 QMessageBox::critical(nullptr, QObject::tr("Verification d'ajout"),
                      QObject::tr("Erreur champ ID vide!.\n"
                                  "Click Cancel to exit."), QMessageBox::Cancel);
                 return false;
             }
       if(lastname.isEmpty()  )

            {
                 QMessageBox::critical(nullptr, QObject::tr("Verification d'ajout"),
                      QObject::tr("Erreur champ NOM vide!.\n"
                                  "Click Cancel to exit."), QMessageBox::Cancel);
                 return false;
             }
       if(name.isEmpty()  )

            {

                 QMessageBox::critical(nullptr, QObject::tr("Verification d'ajout"),
                      QObject::tr("Erreur champ PRENOM vide!.\n"
                                  "Click Cancel to exit."), QMessageBox::Cancel);
                 return false;
             }
       if(address.isEmpty()  )

            {
                 QMessageBox::critical(nullptr, QObject::tr("Verification d'ajout"),
                      QObject::tr("Erreur champ ADRESSE vide!.\n"
                                  "Click Cancel to exit."), QMessageBox::Cancel);
                 return false;
             }

       if(phone==  NULL   )

            {
                 QMessageBox::critical(nullptr, QObject::tr("Verification d'ajout"),
                      QObject::tr("Erreur champ TELEPHONE vide!.\n"
                                  "Click Cancel to exit."), QMessageBox::Cancel);
                 return false;
             }
             if(phone<1000000 || phone>9999999 )
             {
                 QMessageBox::critical(nullptr, QObject::tr("Verification d'ajout"),
                      QObject::tr("numero de telphone non valide !.\n"
                                  "Click Cancel to exit."), QMessageBox::Cancel);
                 return false;
             }
             if(email.indexOf('@')==-1||email.indexOf('.')==-1||email.isEmpty())
             {
                // ui->email_error->setText("votre email doit contenir @");
                 QMessageBox::critical(nullptr, QObject::tr("Verification d'ajout"),
                                   QObject::tr("email doit contenir @ et . !.\n"
                                               "Click Cancel to exit."), QMessageBox::Cancel);
                              return false;
             }



              qDebug()<<query.lastError().text();
    return query.exec();
}
*/
bool Employee::modifier_employee()
{
    QSqlQuery query;
    QString id_string =QString::number(id);
    QString phone_string =QString::number(phone);

    query.prepare("UPDATE employee SET lastname=:lastname, name=:name,email=:email,phone=:phone,address=:address,birthdate=:birthdate,entrydate=:entrydate,poste=:poste where id=:id ");
    query.bindValue(":id",id_string);
    query.bindValue(":lastname",lastname);
    query.bindValue(":name",name);
    query.bindValue(":email",email);
    query.bindValue(":phone",phone_string);
    query.bindValue(":address",address);
    query.bindValue(":birthdate",birthdate);
    query.bindValue(":entrydate",entrydate);
    query.bindValue(":poste",poste);
    return query.exec();
}

bool Employee::supprimer(int id)
{
    QSqlQuery query;

       query.prepare("DELETE from employee where id=:id");
       query.bindValue(":id", id);



    return query.exec();

}


QSqlQueryModel* Employee::afficher()
{
 QSqlQueryModel* model = new QSqlQueryModel();


 model->setQuery("SELECT* FROM employee");
 model->setHeaderData(0, Qt::Horizontal, QObject::tr("Identifiant"));
 model->setHeaderData(1, Qt::Horizontal, QObject::tr("Nom"));
 model->setHeaderData(2, Qt::Horizontal, QObject::tr("Prénom"));
 model->setHeaderData(3, Qt::Horizontal, QObject::tr("Email"));
 model->setHeaderData(4, Qt::Horizontal, QObject::tr("Téléphone"));
 model->setHeaderData(5, Qt::Horizontal, QObject::tr("Adresse"));
 model->setHeaderData(6, Qt::Horizontal, QObject::tr("Date de naissance"));
 model->setHeaderData(7, Qt::Horizontal, QObject::tr("Date d'entrée"));
 model->setHeaderData(8, Qt::Horizontal, QObject::tr("Poste"));

    return model;
}


QSqlQueryModel * Employee:: Stat_employee()
{
    QSqlQueryModel * model=new QSqlQueryModel();
    model->setQuery("SELECT COUNT(*) FROM employee");
    model->setHeaderData(0,Qt::Horizontal,QObject::tr("nombre d'employés"));
    return model;
}


QSqlQueryModel* Employee::trier_anciennete()
{
 QSqlQueryModel* model = new QSqlQueryModel();


 model->setQuery("SELECT * FROM employee ORDER BY entrydate ");
 model->setHeaderData(0, Qt::Horizontal, QObject::tr("Identifiant"));
 model->setHeaderData(1, Qt::Horizontal, QObject::tr("Téléphone"));
 model->setHeaderData(2, Qt::Horizontal, QObject::tr("Prénom"));
 model->setHeaderData(3, Qt::Horizontal, QObject::tr("Nom"));
 model->setHeaderData(4, Qt::Horizontal, QObject::tr("Email"));
 model->setHeaderData(5, Qt::Horizontal, QObject::tr("Adresse"));
 model->setHeaderData(6, Qt::Horizontal, QObject::tr("Date de naissance"));
 model->setHeaderData(7, Qt::Horizontal, QObject::tr("Date d'entrée"));
 model->setHeaderData(8, Qt::Horizontal, QObject::tr("Poste"));

    return model;
}


QSqlQueryModel* Employee::trier_id()
{
 QSqlQueryModel* model = new QSqlQueryModel();


 model->setQuery("SELECT * FROM employee ORDER BY id ");
 model->setHeaderData(0, Qt::Horizontal, QObject::tr("Identifiant"));
 model->setHeaderData(1, Qt::Horizontal, QObject::tr("Téléphone"));
 model->setHeaderData(2, Qt::Horizontal, QObject::tr("Prénom"));
 model->setHeaderData(3, Qt::Horizontal, QObject::tr("Nom"));
 model->setHeaderData(4, Qt::Horizontal, QObject::tr("Email"));
 model->setHeaderData(5, Qt::Horizontal, QObject::tr("Adresse"));
 model->setHeaderData(6, Qt::Horizontal, QObject::tr("Date de naissance"));
 model->setHeaderData(7, Qt::Horizontal, QObject::tr("Date d'entrée"));
 model->setHeaderData(8, Qt::Horizontal, QObject::tr("Poste"));

    return model;
}

QSqlQueryModel* Employee::trier_age()
{
 QSqlQueryModel* model = new QSqlQueryModel();


 model->setQuery("SELECT * FROM employee ORDER BY birthdate DESC ");
 model->setHeaderData(0, Qt::Horizontal, QObject::tr("Identifiant"));
 model->setHeaderData(1, Qt::Horizontal, QObject::tr("Téléphone"));
 model->setHeaderData(2, Qt::Horizontal, QObject::tr("Prénom"));
 model->setHeaderData(3, Qt::Horizontal, QObject::tr("Nom"));
 model->setHeaderData(4, Qt::Horizontal, QObject::tr("Email"));
 model->setHeaderData(5, Qt::Horizontal, QObject::tr("Adresse"));
 model->setHeaderData(6, Qt::Horizontal, QObject::tr("Date de naissance"));
 model->setHeaderData(7, Qt::Horizontal, QObject::tr("Date d'entrée"));
 model->setHeaderData(8, Qt::Horizontal, QObject::tr("Poste"));

    return model;
}
QSqlQueryModel * Employee::rechercher_employee(const QString &b)
{
    QSqlQueryModel * model=new QSqlQueryModel();
    model->setQuery("SELECT * FROM employee WHERE (id || lastname || name || email || phone || address || birthdate || entrydate || poste) LIKE '%"+b+"%'");
 model->setHeaderData(0, Qt::Horizontal, QObject::tr("Identifiant"));
 model->setHeaderData(1, Qt::Horizontal, QObject::tr("Téléphone"));
 model->setHeaderData(2, Qt::Horizontal, QObject::tr("Prénom"));
 model->setHeaderData(3, Qt::Horizontal, QObject::tr("Nom"));
 model->setHeaderData(4, Qt::Horizontal, QObject::tr("Email"));
 model->setHeaderData(5, Qt::Horizontal, QObject::tr("Adresse"));
 model->setHeaderData(6, Qt::Horizontal, QObject::tr("Date de naissance"));
 model->setHeaderData(7, Qt::Horizontal, QObject::tr("Date d'entrée"));
 model->setHeaderData(8, Qt::Horizontal, QObject::tr("Poste"));

    return model;
}

QSqlQueryModel * Employee::recherche_emp_complete()
 {
     QSqlQueryModel * model=new QSqlQueryModel();
     model->setQuery("SELECT lastname FROM employee");
     return model;




}




QSqlQueryModel* Employee::fiche()
{
 QSqlQueryModel* model = new QSqlQueryModel();


 model->setQuery("SELECT entrydate FROM employee");


    return model;
}

