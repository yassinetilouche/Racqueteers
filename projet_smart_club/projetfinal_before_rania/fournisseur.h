#ifndef FOURNISSEUR_H
#define FOURNISSEUR_H
#include <QDate>
#include <QString>
#include <QSqlQueryModel>
#include <QSqlTableModel>


class Fournisseur
{
public:
    Fournisseur();
    Fournisseur(int,int,float,QString,QString,QString);
    int getid_fournisseur();
    int gettelephone();
    float getfacture();
    QString getnom();
    QString getprenom();
    QString getentreprise();


    void setid_fournisseur(int);
    void settelephone(int);
    void setfacture(float);
    void setnom(QString);
    void setprenom(QString);
    void setentreprise(QString);

    QSqlQueryModel* afficher_f();
    QSqlTableModel* afficherf();
    QStringList ajouterf();
    bool supprimerf(int);
    QStringList changerf();
    QSqlQuery lister_f();
    QStringList list;
    QSqlQuery lister();

private:
    int id_fournisseur;
    int telephone;
    float facture;
    QString nom;
    QString prenom;
    QString entreprise;

};

#endif // FOURNISSEUR_H


