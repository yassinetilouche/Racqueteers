#ifndef POSTE_H
#define POSTE_H
#include <QString>
#include <QDate>
#include <QSqlQueryModel>
#include <QtDebug>
#include <QSqlError>



class Poste
{
public:
    Poste();
    Poste(int,QString,int,int,int);
    int getemployee_nb();
    int getid_poste();
    int getlevel();
    int getsalary();
    QString gettitle();

    void setemployee_nb(int);
    void setid_poste(int);
    void setlevel(int);
    void setsalary(int);
    void settitle(QString);
    QString ajouter_poste();

    //bool ajouter_poste();
    bool modifier_poste();
    QSqlQueryModel* afficher_postes();
    bool supprimer_poste(int);
    QSqlQueryModel * Stat_poste();
    QSqlQueryModel* trier_niveau();
    QSqlQueryModel* trier_salaire();
    QSqlQueryModel* trier_nb_employees();
    QSqlQueryModel * rechercher_poste(const QString &b);



private:
    int employee_number,hierarchical_level,id_poste,salary;
    QString title_poste;


};




#endif // POSTE_H
