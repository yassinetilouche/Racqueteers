#ifndef ADHERENT_H
#define ADHERENT_H
#include <QString>
#include <QDate>
#include <QSqlQueryModel>

class Adherent
{
public:
    int mailt;
    int numtelt;
    int datet;
    Adherent();
    Adherent(int,QString,QString,QString,QString,QString,int,QString);
    int getid();
    int getmailt();
    int getnumtel(){return num_tel;}
    int getdatet();
    int getnumtelt();
    QString getnom();
    QString getprenom();
    QString getsexe();
    QString getdate();
    void setid(int);
    void setnom(QString);
    void setprenom(QString);
    void setsexe(QString);
    void setdate(QString);
    bool ajouter();
    bool supprimer_adherent(int);
    QSqlQueryModel* afficher_adherent();
    bool modifier();
    QSqlQueryModel *chercher_adherent(QString );
    QSqlQueryModel * rechercher_com();
private:
    int id_Adherant,num_tel;
    QString nom,prenom,sexe,email,adresse;
    QString Date_de_Naissance;

};

#endif // ADHERENT_H
