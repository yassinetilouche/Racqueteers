#ifndef ABONNEMET_H
#define ABONNEMET_H
#include <QString>
#include <QSqlQueryModel>
#include <QDate>
class abonnemet
{
private:
    int code;
    QString nomC;
    QString dateD, dateF;
    float prix ;
public:
    abonnemet();
    abonnemet(int,QString,QString,QString,float);
    int getCode(){return code;}
    QString getNomC(){return nomC;}
    QString getDateD(){return dateD;}
    QString getDateF(){return dateF;}
    float getPrix(){return prix;}
    void setCode(int a){code=a;}
    void setNomC(QString a){nomC=a;}
    void setDateD(QString a){dateD=a;}
    void setDateF(QString a){dateF=a;}
    void setPrix(float a){prix=a;}
    QSqlQueryModel* afficher();
    bool ajouter();
    bool supprimer(int);
    bool modifier_abonnement();
    QSqlQueryModel * rechercher(QString);
};

#endif // ABONNEMET_H
