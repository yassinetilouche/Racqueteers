#ifndef COURS_H
#define COURS_H
#include <QString>
#include <QSqlQueryModel>
#include <QSqlQuery>

class cours
{
public:
    cours();
    cours(int,QString,int,int,int);
    int get_idCours();
    QString get_titre();
    int get_nbrObj();
    int get_nbrPrt();
    int get_nbrSeances();

    bool ajouter();
    QSqlQueryModel * afficher();
    QSqlQueryModel * affichertri(int);
    bool supprimer(int);
    bool modifier(int);
private:
    int id_cours,nombre_objectif,nombre_participants,nombre_de_seances_requises;
    QString titre;
};

#endif // COURS_H
