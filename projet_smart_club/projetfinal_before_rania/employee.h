#ifndef EMPLOYEE_H
#define EMPLOYEE_H
#include <QString>
#include <QDate>
#include <QSqlQueryModel>


class Employee
{
public:
   Employee();
   Employee(int,QString,QString,QString,int,QString,QDate,QDate,QString);
   int getid();
   int getphone();
   QString getlastname();
   QString getname();
   QString getemail();
   QString getaddress();
   QDate getbirthdate();
   QDate getentrydate();
   QString getposte();

   void setid(int);
   void setphone(int);
   void setlastname(QString);
   void setname(QString);
   void setemail(QString);
   void setaddress(QString);
   void setbirthdate(QDate);
   void setentrydate(QDate);
   void setposte(QString);
    //int ajouter();
  // bool ajouter();
   QString ajouter();
   bool modifier_employee();
   QSqlQueryModel* afficher();
   bool supprimer(int);
   QSqlQueryModel * Stat_employee();
   QSqlQueryModel* trier_anciennete();
   QSqlQueryModel* trier_id();
   QSqlQueryModel* trier_age();
   QSqlQueryModel * rechercher_employee(const QString &b);
   QSqlQueryModel* fiche();
   QSqlQueryModel * recherche_emp_complete();



private:
   int id,phone;
   QString name,lastname,email,address,poste;
   QDate birthdate,entrydate;


};


#endif // EMPLOYEE_H
