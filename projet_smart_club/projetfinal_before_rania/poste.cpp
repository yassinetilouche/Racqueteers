#include "poste.h"
#include <QSqlQuery>
#include <QtDebug>
#include <QDate>
#include <QObject>
#include <QMessageBox>
Poste::Poste()
{
id_poste=0;
}
Poste::Poste(int id_poste ,QString title_poste,int salary,int hierarchical_level,int employee_number)
{
    this->id_poste=id_poste;
    this->title_poste=title_poste;
    this->salary=salary;
    this->hierarchical_level=hierarchical_level;
    this->employee_number=employee_number;
}

int Poste::getid_poste(){return id_poste ;}
QString Poste::gettitle(){return title_poste  ;}
int Poste::getsalary(){return salary ;}
int Poste::getlevel(){return hierarchical_level ;}
int Poste::getemployee_nb(){return  employee_number;}

void Poste::setemployee_nb(int employee_number){this->employee_number=employee_number;}
void Poste::setid_poste(int id_poste){this->id_poste=id_poste;}
void Poste::setlevel(int hierarchical_level){this->hierarchical_level=hierarchical_level;}
void Poste::setsalary(int salary){this->salary=salary;}
void Poste::settitle(QString title_poste){this->title_poste=title_poste;}




QString Poste::ajouter_poste(){

    QSqlQuery query;
       QString test="";
       QString id_poste_string =QString::number(id_poste);
       QString employee_number_string =QString::number(employee_number);
       QString h_level_string =QString::number(hierarchical_level);
       QString salary_string =QString::number(salary);


       query.prepare("INSERT INTO poste (id_poste, title_poste, salary,hierarchical_level,employee_number) "
                     "VALUES (:id_poste, :title_poste, :salary, :hierarchical_level, :employee_number)");
       query.bindValue(":id_poste",id_poste_string );
       query.bindValue(":title_poste", title_poste);
       query.bindValue(":salary", salary_string);
       query.bindValue(":hierarchical_level", h_level_string);
       query.bindValue(":employee_number", employee_number_string);

        if(id_poste==NULL  )
              {
                  test=test+"2";
              }
         if (hierarchical_level==  NULL)
        {
            test=test+"3";
        }
        if( salary== NULL )
                         {
                             test=test+"4";
                         }
         if( title_poste.isEmpty() )
       {

           test=test+"5";
       }

         if(employee_number== NULL)
       {

           test=test+"6";
       }

             if (test=="")
             {
                 query.exec();
             }

               qDebug()<<query.lastError().text();

             qDebug() <<test;

     return test; }



/*


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


*/
/*
QString Poste::ajouter_poste(){

    QSqlQuery query;
       QString id_poste_string =QString::number(id_poste);
       QString employee_number_string =QString::number(employee_number);
       QString h_level_string =QString::number(hierarchical_level);
       QString salary_string =QString::number(salary);


       query.prepare("INSERT INTO poste (id_poste, title_poste, salary,hierarchical_level,employee_number) "
                     "VALUES (:id_poste, :title_poste, :salary, :hierarchical_level, :employee_number)");
       query.bindValue(":id_poste",id_poste_string );
       query.bindValue(":title_poste", title_poste);
       query.bindValue(":salary", salary_string);
       query.bindValue(":hierarchical_level", h_level_string);
       query.bindValue(":employee_number", employee_number_string);

        if(id_poste==NULL  )
              {
                  QMessageBox::critical(nullptr, QObject::tr("Verification d'ajout"),
                       QObject::tr("Erreur champ poste vide !.\n"
                                   "Click Cancel to exit."), QMessageBox::Cancel);
                  return false;
              }
        else if (hierarchical_level==  NULL)
        {

            QMessageBox::critical(nullptr, QObject::tr("Verification d'ajout"),
                 QObject::tr("champ niveau  vide !.\n"
                             "Click Cancel to exit."), QMessageBox::Cancel);
            return false;
        }
       else if( salary== NULL )
                         {
                             QMessageBox::critical(nullptr, QObject::tr("Verification d'ajout"),
                                  QObject::tr("Erreur champ salaire vide !.\n"
                                              "Click Cancel to exit."), QMessageBox::Cancel);
                             return false;
                         }
       else  if( title_poste.isEmpty() )
       {
           QMessageBox::critical(nullptr, QObject::tr("Verification d'ajout"),
                QObject::tr("Erreur champ titre vide !.\n"
                            "Click Cancel to exit."), QMessageBox::Cancel);
           return false;
       }

       else  if(employee_number== NULL)
       {
           QMessageBox::critical(nullptr, QObject::tr("Verification d'ajout"),
                QObject::tr("Erreur champ nombre employés vide !.\n"
                            "Click Cancel to exit."), QMessageBox::Cancel);
           return false;
       }

    return query.exec();
}*/
QSqlQueryModel* Poste::afficher_postes()
{
 QSqlQueryModel* model = new QSqlQueryModel();
 model->setQuery("SELECT* FROM poste");

    return model;
}


bool Poste::modifier_poste()
{
    QSqlQuery query;
    QString id_poste_string =QString::number(id_poste);
    QString employee_number_string =QString::number(employee_number);
    QString h_level_string =QString::number(hierarchical_level);
    QString salary_string =QString::number(salary);

    query.prepare("UPDATE poste SET title_poste=:title_poste, salary=:salary ,hierarchical_level=:hierarchical_level,employee_number=:employee_number  where id_poste=:id_poste ");
    query.bindValue(":id_poste",id_poste_string );
    query.bindValue(":title_poste", title_poste);
    query.bindValue(":salary", salary_string);
    query.bindValue(":hierarchical_level", h_level_string);
    query.bindValue(":employee_number", employee_number_string);
    return query.exec();

}

bool Poste::supprimer_poste(int id_poste)
{
    QSqlQuery query;

       query.prepare("DELETE from poste where id_poste=:id_poste");
       query.bindValue(":id_poste", id_poste);



    return query.exec();

}
QSqlQueryModel * Poste:: Stat_poste()
{
    QSqlQueryModel * model=new QSqlQueryModel();
    model->setQuery("SELECT COUNT(*) FROM poste");
    model->setHeaderData(0,Qt::Horizontal,QObject::tr("nombre de postes"));
    return model;
}






QSqlQueryModel* Poste::trier_salaire()
{
 QSqlQueryModel* model = new QSqlQueryModel();


 model->setQuery("SELECT * FROM poste ORDER BY salary   ");
    return model;
}




QSqlQueryModel* Poste::trier_niveau()
{
 QSqlQueryModel* model = new QSqlQueryModel();


 model->setQuery("SELECT * FROM poste ORDER BY hierarchical_level  ");
    return model;
}



QSqlQueryModel* Poste::trier_nb_employees()
{
 QSqlQueryModel* model = new QSqlQueryModel();


 model->setQuery("SELECT * FROM poste ORDER BY employee_number DESC ");
    return model;
}

QSqlQueryModel * Poste::rechercher_poste(const QString &b)
{
    QSqlQueryModel * model=new QSqlQueryModel();
    model->setQuery("SELECT * FROM poste WHERE (id_poste || title_poste || salary||hierarchical_level||employee_number) LIKE '%"+b+"%'");


    return model;
}
/*
 * testing git 21/02/2021 on 14.30
 *
 *
 *
 *
 * Poste::Poste(int id_poste ,QString title_poste,int salary,int hierarchical_level,int employee_number)
{
    this->id_poste=id_poste;
    this->title_poste=title_poste;
    this->salary=salary;
    this->hierarchical_level=hierarchical_level;
    this->employee_number=employee_number;
}

int Poste::getid_poste(){return id_poste ;}
QString Poste::gettitle(){return title_poste  ;}
int Poste::getsalary(){return salary ;}
int Poste::getlevel(){return hierarchical_level ;}
int Poste::getemployee_nb(){return  employee_number;}

void Poste::setemployee_nb(int employee_number){this->employee_number=employee_number;}
void Poste::setid_poste(int id_poste){this->id_poste=id_poste;}
void Poste::setlevel(int hierarchical_level){this->hierarchical_level=hierarchical_level;}
void Poste::setsalary(int salary){this->salary=salary;}
void Poste::settitle(QString title_poste){this->title_poste=title_poste;}
*/
