#ifndef ENTREPRISE_H
#define ENTREPRISE_H
#include <QString>
#include <QSqlQueryModel>
#include <QSqlTableModel>
#include <QDate>
#include <QDateEdit>
class Entreprise
{
public:
    Entreprise();
    Entreprise(int,QString,QString,QString,int,QString,QDate);

    int getid_entreprise();
    QString getnom_E();
    QString getville();
    QString getrue();
    int getcode_postal();
    QString getemail();
    QDate getdate_colab();

    void setid_entreprise(int);
    void setnom_E(QString );
    void setville(QString );
    void setrue(QString );
    void setcode_postal(int);
    void setemail(QString );
    void setdate_colab(QDate);

    QStringList ajouter();
    QSqlTableModel* afficher();
    bool supprimer(int);
    QStringList modifier();

    QSqlQueryModel* trier();
    QSqlQueryModel* charger();
   QSqlQueryModel* rechercher(QString);
    QSqlQuery lister();
    QStringList list;
    QSqlQuery exist(int);

private:
    int id_entreprise;
    QString nom_E;
    QString ville;
    QString rue;
    int code_postal;
    QString email;
    QDate date_colab;

};


#endif // ENTREPRISE_H
