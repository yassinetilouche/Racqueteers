#ifndef SEANCES_H
#define SEANCES_H
#include<QString>
#include<QSqlQueryModel>
#include <QSqlQuery>

class seances
{
public:
    seances();
    seances(int,QString , QString , QString , QString , int);
      int get_id();
      QString get_date();
      QString get_hrdb();
      QString get_hrfn();
      QString get_lieu();
      int get_prix();

      bool ajouter();
      QSqlQueryModel * afficher();
      QSqlQueryModel * affichertri(int);

      bool supprimer(int);
      bool modifier(int);

private :
      int   id_seance ,prix_seance;
      QString date_seance,heure_debut,heure_fin,lieu;
};

#endif // SEANCES_H
