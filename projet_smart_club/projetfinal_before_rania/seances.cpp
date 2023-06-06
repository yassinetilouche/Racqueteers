#include "seances.h"

seances::seances()
{
    int id_seance = 0 ;
    QString date_seance = "";
    QString heure_debut = "";
    QString heure_fin = "";
    QString lieu = "";
    int prix_seance = 0 ;

}
seances::seances(int id_seance,QString date_seance , QString heure_debut , QString heure_fin , QString lieu ,int prix_seance )
{
    this-> id_seance=id_seance  ;
    this-> date_seance= date_seance ;
    this-> heure_debut=heure_debut ;
    this-> heure_fin=heure_fin ;
    this-> lieu=lieu ;
    this-> prix_seance = prix_seance  ;
}
int seances::get_id(){return id_seance;}
QString seances::get_date(){return date_seance;}
QString seances::get_hrdb(){return heure_debut;}
QString seances::get_hrfn(){return heure_fin;}
QString seances::get_lieu(){return lieu;}
int seances::get_prix(){return prix_seance ;}

bool seances::ajouter(){
    QSqlQuery query;
    query.prepare("INSERT INTO SEANCES (id_seance,date_seance,heure_debut,heure_fin,lieu,prix_seance)"
                "Values(:id_seance,:date_seance,:heure_debut,:heure_fin,:lieu,:prix_seance)");
    query.bindValue(":id_seance",id_seance);
    query.bindValue(":date_seance",date_seance);
    query.bindValue(":heure_debut",heure_debut);
    query.bindValue(":heure_fin",heure_fin);
    query.bindValue(":lieu",lieu);
    query.bindValue(":prix_seance",prix_seance);
   return  query.exec();
}

QSqlQueryModel * seances::afficher()
{QSqlQueryModel * model= new QSqlQueryModel();
    model->setQuery("SELECT * FROM SEANCES order by id_seance ");
    model->setHeaderData(0, Qt::Horizontal, QObject::tr("ID SEANCE"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("DATE"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("HEURE DEBUT"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("HEURE FIN"));
    model->setHeaderData(4, Qt::Horizontal, QObject::tr("LIEU"));
    model->setHeaderData(5, Qt::Horizontal, QObject::tr("PRIX"));
    return model;
}
bool seances::supprimer(int id_seance)
{
    QSqlQuery query;
    query.prepare("Delete from SEANCES where id_seance=:id_seance ");
    query.bindValue(":id_seance",id_seance);
    return query.exec();
}
bool seances::modifier(int id_seance)
{
    QSqlQuery query;
    query.prepare("UPDATE SEANCES set id_seance=:id_seance,date_seance=:date_seance,heure_debut=:heure_debut,heure_fin=:heure_fin,lieu=:lieu,prix_seance =:prix_seance where id_seance=:id_seance ");
    query.bindValue(":id_seance",id_seance);
    query.bindValue(":date_seance",date_seance);
    query.bindValue(":heure_debut",heure_debut);
    query.bindValue(":heure_fin",heure_fin);
    query.bindValue(":lieu",lieu);
    query.bindValue(":prix_seance",prix_seance);

    return query.exec();
}
QSqlQueryModel * seances::affichertri(int choix)
{QSqlQueryModel * model= new QSqlQueryModel();
    switch (choix) {
    case 0 : model->setQuery("SELECT * FROM SEANCES order by id_seance asc ");
    break;
    case 1 : model->setQuery("SELECT * FROM SEANCES order by id_seance desc ");
        break;
    case 2 : model->setQuery("SELECT * FROM SEANCES order by date_seance ");
        break;
    case 3 : model->setQuery("SELECT * FROM SEANCES order by date_seance desc");
        break;
    case 4 : model->setQuery("SELECT * FROM SEANCES order by heure_debut ");
        break;
    case 5: model->setQuery("SELECT * FROM SEANCES order by heure_debut desc");
        break;
    case 6 : model->setQuery("SELECT * FROM SEANCES order by heure_fin ");
        break;
    case 7 : model->setQuery("SELECT * FROM SEANCES order by heure_fin desc");
        break;
    case 8 : model->setQuery("SELECT * FROM SEANCES order by lieu ");
        break;
    case 9 : model->setQuery("SELECT * FROM SEANCES order by lieu desc ");
        break;
    case 10 : model->setQuery("SELECT * FROM SEANCES order by prix_seance ");
        break;
    case 11 : model->setQuery("SELECT * FROM SEANCES order by prix_seance desc");
        break;
    default : model->setQuery("SELECT * FROM SEANCES order by id_seance ");

    }

    model->setHeaderData(0, Qt::Horizontal, QObject::tr("ID SEANCE"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("DATE"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("HEURE DEBUT"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("HEURE FIN"));
    model->setHeaderData(4, Qt::Horizontal, QObject::tr("LIEU"));
    model->setHeaderData(5, Qt::Horizontal, QObject::tr("PRIX"));
    return model;
}
