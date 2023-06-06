#ifndef EVENEMENT_H
#define EVENEMENT_H
#include <QString>
#include <QSqlQueryModel>
#include <QVector>

class Evenement
{
public:
    Evenement();
    Evenement(int,QString,QString,QString,int,QString);
    int getId();
    QString getType();
    QString getDate();
    QString getHeure();
    int getNbr();
    QString getLieu();
    void setType(QString);
    void setDate(QString);
    void setHeure(QString);
    void setNbr(int);
    void setLieu(QString);
    bool ajouter();
    QSqlQueryModel* afficher();
    bool supprimer(int);
    bool modifier(int);
    QSqlQueryModel* rechercher(QString);
    QSqlQueryModel* triDesc();
    QSqlQueryModel* triAsc();
    void pdf(QString);
    int number();
    QSqlQueryModel* rechercherEvenement();
    QVector<double> data_from_Base(int m, int y);
private:
    int id;
    QString type;
    QString date_debut;
    QString heure_debut;
    int nombrePlace;
    QString lieu;
};

#endif // EVENEMENT_H
