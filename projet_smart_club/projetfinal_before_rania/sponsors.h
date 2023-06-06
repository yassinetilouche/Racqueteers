#ifndef SPONSORS_H
#define SPONSORS_H
#include <QString>
#include <QSqlQueryModel>

class Sponsors
{
public:
    Sponsors();
    Sponsors(int, int, QString, QString, QString, QString);
    bool ajouter();
    bool supprimer(int);
    QSqlQueryModel* afficher();
    bool modifier(int);
    QSqlQueryModel* rechercher(QString);
    QSqlQueryModel* triDesc();
    QSqlQueryModel* triAsc();
    //QString getTel();
    QString getEmail();
    QString getType();
    QString getMateriels();
private:
    int id;
    int tel;
    QString nom_e;
    QString email;
    QString type;
    QString materiels;
};

#endif // SPONSORS_H
