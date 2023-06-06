#ifndef MATCH_H
#define MATCH_H
#include <QString>
#include <QDate>
#include <QSqlQueryModel>


class Match
{
public:
    Match();
    Match(int,QString,int,QString,int);
    bool ajouter_match();
    QSqlQueryModel* affichermatchs();
    QSqlQueryModel * recherche_player_complete();

private:
   QString first_player_name;
   QString second_player_name;
   int match_id;
   int first_player_score;
   int second_player_score;

};

#endif // MATCH_H
