#include "match.h"
#include <QSqlQuery>
#include <QtDebug>
#include <QDate>
#include <QObject>
#include <QMessageBox>
Match::Match()
{
match_id=0;
}


Match::Match(int match_id,QString first_player_name,int first_player_score,QString second_player_name,int second_player_score)
{
    this->match_id=match_id;
    this->first_player_name=first_player_name;
    this->first_player_score=first_player_score;
    this->second_player_name=second_player_name;
    this->second_player_score=second_player_score;
}
bool Match::ajouter_match()
{
    QSqlQuery query;

    QString match_id_string =QString::number(match_id);
    QString score1_string =QString::number(first_player_score);
    QString score2_string =QString::number(second_player_score);

    query.prepare("INSERT INTO match ( match_id, first_player_name, first_player_score, second_player_name, second_player_score) "
                  "VALUES ( :match_id, :first_player_name, :first_player_score, :second_player_name, :second_player_score)");
    query.bindValue(":match_id",match_id_string );
    query.bindValue(":first_player_name", first_player_name);
    query.bindValue(":first_player_score", score1_string);
    query.bindValue(":second_player_name", second_player_name);
    query.bindValue(":second_player_score", score2_string);
     return query.exec();

}

QSqlQueryModel* Match::affichermatchs()
{
 QSqlQueryModel* model = new QSqlQueryModel();
 model->setQuery("SELECT* FROM match");

    return model;
}

QSqlQueryModel * Match::recherche_player_complete()
 {
     QSqlQueryModel * model=new QSqlQueryModel();
     model->setQuery("SELECT nom||prenom FROM Adherent");
     return model;

}
