#ifndef EQUIPEMENT_H
#define EQUIPEMENT_H
#include <QString>
#include <QSqlQueryModel>
#include <QSqlTableModel>

class Equipement
{
public:
    Equipement();
    Equipement(int,QString,int,QString,float,QString);

    int getid_equipement();
    int getnombre();
    QString getetat();
    QString gettype();
    float getprix();
    QString getdisponibilite();

    void setid_equipement(int);
    void setnombre(int);
    void setetat(QString );
    void settype(QString );
    void setprix(float);
    void setdisponibilite(QString);


    QStringList ajouter();
    QSqlTableModel* afficher();
    QSqlQueryModel* trier();
    QSqlQueryModel* charger();
    QSqlQueryModel* rechercher(QString);
    QSqlQuery lister();
    int recherche(QString,QString);
    bool pdf();
    bool supprimer(int);
    QStringList changer();
   // bool existe(int);
    QStringList list;
    QSqlQuery lister(QString);

private:
    int id_equipement;
    int nombre;
    QString etat;
    QString type;
    float prix;
    QString disponibilite;
};

#endif // EQUIPEMENT_H
