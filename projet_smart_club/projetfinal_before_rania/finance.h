#ifndef FINANCE_H
#define FINANCE_H
#include <QString>
#include <QSqlQueryModel>

class finance
{
public:

    finance();
    finance(int,QString,QString,QString,float);
    int getId();
    QString getType();
    QString getDate();
    QString getDescription();
    float getPrix();
    void setId(int);
    void setType(QString);
    void setDate(QString);
    void setDescription(QString);
    void setPrix(float);
    bool ajouter();
    QSqlQueryModel * afficher();
    bool supprimer(int);
    bool modifier_finance();
    QSqlQueryModel * rechercher(QString);
    QSqlQueryModel * trieFinanace();
private:
    int id ;
    QString type,date,description;
    float prix;

};

#endif // FINANCE_H
