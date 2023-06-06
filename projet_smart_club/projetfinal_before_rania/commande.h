#ifndef COMMANDE_H
#define COMMANDE_H
#include <QString>
#include <QSqlQueryModel>
#include <QSqlTableModel>
#include <QDate>
#include <QDateEdit>

class commande
{
public:
    commande();
    commande(int,QDate,int,QString,int);

    int getid_commande();
    QDate getdate_commande();
    int getid_f();
    QString gettype_commande();
    int getid_eq();

    void setid_commande(int);
    void setdate_commande(QDate);
    void setid_f(int);
    void settype_commande(QString);
    void setid_eq(int);

    QStringList ajouter();
    QSqlTableModel* afficher();
    bool supprimer(int);
    QStringList modifier();

    QSqlQueryModel* trier();
    QSqlQueryModel* charger();
   QSqlQueryModel* rechercher(QString);
    QSqlQuery lister();
    QStringList list;

private:
    int id_commande;
    QDate date_commande;
    int id_f;
    QString type_commande;
    int id_eq;


};

#endif // COMMANDE_H
