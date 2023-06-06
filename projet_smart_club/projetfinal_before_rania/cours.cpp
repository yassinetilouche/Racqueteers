#include "cours.h"

cours::cours()
{
 int id_cours = 0 ;
 QString titre = "";
 int nombre_objectif = 0;
 int nombre_participants = 0;
 int nombre_de_seances_requises =0;
}
cours::cours(int id_cours,QString titre ,int nombre_objectif ,int nombre_participants ,int nombre_de_seances_requises )
{
    this-> id_cours=id_cours  ;
    this-> titre= titre ;
    this-> nombre_objectif=nombre_objectif ;
    this-> nombre_participants=nombre_participants ;
    this-> nombre_de_seances_requises=nombre_de_seances_requises ;

}
int cours::get_idCours(){return id_cours;}
QString cours::get_titre(){return titre;}
int cours::get_nbrObj(){return nombre_objectif;}
int cours::get_nbrPrt(){return nombre_participants ;}
int cours::get_nbrSeances(){return nombre_de_seances_requises;}

bool cours::ajouter(){
    QSqlQuery query;
    query.prepare("INSERT INTO cours (id_cours,titre,nombre_objectif,nombre_participants,nombre_de_seances_requises)"
                "Values(:id_cours,:titre,:nombre_objectif,:nombre_participants,:nombre_de_seances_requises)");
    query.bindValue(":id_cours",id_cours);
    query.bindValue(":titre",titre);
    query.bindValue(":nombre_objectif",nombre_objectif);
    query.bindValue(":nombre_participants",nombre_participants);
    query.bindValue(":nombre_de_seances_requises",nombre_de_seances_requises);

   return  query.exec();
}

QSqlQueryModel * cours::afficher()
{QSqlQueryModel * model= new QSqlQueryModel();
    model->setQuery("SELECT * FROM cours order by id_cours ");
    model->setHeaderData(0, Qt::Horizontal, QObject::tr("ID COUR"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("TITRE"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("NBR OBJECTIF"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("NBR PARTICIPANTS"));
    model->setHeaderData(4, Qt::Horizontal, QObject::tr("NBR SEANCES REQUISES"));

    return model;
}
bool cours::supprimer(int id_cours)
{
    QSqlQuery query;
    query.prepare("Delete from COURS where id_cours=:id_cours ");
    query.bindValue(":id_cours",id_cours);
    return query.exec();
}
bool cours::modifier(int id_cours)
{
    QSqlQuery query;
    query.prepare("UPDATE cours set id_cours=:id_cours,titre=:titre,nombre_objectif=:nombre_objectif,nombre_participants=:nombre_participants,nombre_de_seances_requises=:nombre_de_seances_requises where id_cours=:id_cours ");
    query.bindValue(":id_cours",id_cours);
    query.bindValue(":titre",titre);
    query.bindValue(":nombre_objectif",nombre_objectif);
    query.bindValue(":nombre_participants",nombre_participants);
    query.bindValue(":nombre_de_seances_requises",nombre_de_seances_requises);

    return query.exec();
}
QSqlQueryModel * cours::affichertri(int choix){
    QSqlQueryModel * model= new QSqlQueryModel();
        switch (choix)
        {
        case 0 : model->setQuery("SELECT * FROM cours order by id_cours ");
        break;
        case 1 : model->setQuery("SELECT * FROM cours order by id_cours desc ");
            break;
        case 2 : model->setQuery("SELECT * FROM cours order by titre  ");
            break;
        case 3 : model->setQuery("SELECT * FROM cours order by titre desc ");
            break;
        case 4 : model->setQuery("SELECT * FROM cours order by nombre_objectif ");
            break;
        case 5: model->setQuery("SELECT * FROM cours order by nombre_objectif desc ");
            break;
        case 6 : model->setQuery("SELECT * FROM cours order by nombre_participants  ");
            break;
        case 7 : model->setQuery("SELECT * FROM cours order by nombre_participants desc ");
            break;
        case 8 : model->setQuery("SELECT * FROM cours order by nombre_de_seances_requises ");
            break;
        case 9 : model->setQuery("SELECT * FROM cours order by nombre_de_seances_requises desc  ");
            break;
        default : model->setQuery("SELECT * FROM cours order by id_cours  ");

        }
        model->setHeaderData(0, Qt::Horizontal, QObject::tr("ID COUR"));
        model->setHeaderData(1, Qt::Horizontal, QObject::tr("TITRE"));
        model->setHeaderData(2, Qt::Horizontal, QObject::tr("NBR OBJECTIF"));
        model->setHeaderData(3, Qt::Horizontal, QObject::tr("NBR PARTICIPANTS"));
        model->setHeaderData(4, Qt::Horizontal, QObject::tr("NBR SEANCES REQUISES"));

        return model;


}
