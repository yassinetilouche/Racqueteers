#ifndef LOGIN_H
#define LOGIN_H
#include<QString>

class login
{
private:
    QString nom,prenom;
    int age;
    QString username , mdp;
    int telephone;
public:
    login();
    login(QString,QString,int,QString,QString,int);
    QString getNom(){return nom;}
    QString getPrenom(){return prenom;}
    int getAge(){return age;}
    QString getUsername(){return username;}
    QString getMdp(){return mdp;}
    int getTelephone(){return telephone;}
    void setNom(QString){}
    void setPrenom(QString){}
    void setAge(int){}
    void setUsername(QString){}
    void setMdp(QString){}
    void setTelephone(){}
    bool ajouter();
};

#endif // LOGIN_H
