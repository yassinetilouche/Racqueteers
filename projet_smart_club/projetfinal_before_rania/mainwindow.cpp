#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>
#include "gestionequipement.h"
#include "GestionAdherent.h"
#include "gestionfinance.h"
#include "gestionpersonnel.h"
#include "gestionevenement.h"
#include <QPrintDialog>
#include "login.h"
#include <QtWidgets>
#include <QSqlQuery>


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow){
    ui->setupUi(this);
    QPixmap pix("C:/Users/Yassine/Downloads/tennislogo.png");
    int w =ui->logo->width();
    int h=ui->logo->height();
    ui->logo->setPixmap(pix.scaled(w,h,Qt::KeepAspectRatio));
}


MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_pb_gestion_materiels_clicked()
{
    hide();
    GE = new gestionequipement(this);
    GE->show();
}

void MainWindow::on_pushButton_singIn_clicked()
{
    QString username=ui->lineEdit_username->text();
       QString mdp=ui->lineEdit_mdp->text();
       int n = username.size();
       int n1 = mdp.size();
       if ((n != 0  or n1  != 0)  ) {


         if (n>3 and n<11)

         {
             if (n1>5 and n1<21 )
             {


              QSqlQuery query;
                  query.prepare("SELECT * FROM LOGIN WHERE USERNAME= ? AND mdp= ?");
                  query.addBindValue(username);
                  query.addBindValue(mdp);
                   query.exec();

                     if(query.next())

                     {
                         QMessageBox::information(nullptr, QObject::tr("LOGIN"),
                                                             QObject::tr("\nvous avez connecté avec succès !\n"), QMessageBox::Ok);

                         ui->stackedWidget->setCurrentIndex(2);

                      }
                           else
                              { QMessageBox::critical(nullptr, QObject::tr("LOGIN"),
                                           QObject::tr("\nvotre mot de passe ou votre nom est incorrect !\n"), QMessageBox::Cancel);
                      ui->lineEdit_username->setStyleSheet("border: 1px solid red");
                      ui->lineEdit_mdp->setStyleSheet("border: 1px solid red");

                     ui->lineEdit_username->clear();
                     ui->lineEdit_mdp->clear();}

             }
             else
             { QMessageBox::critical(nullptr, QObject::tr("LOGIN"),
                                         QObject::tr("\n votre mot passe doit etre entre \n"
                                                     "6 et 21 characteres"), QMessageBox::Cancel);
                 ui->lineEdit_mdp->setStyleSheet("border: 1px solid red");
             }
         }

         else
            {  QMessageBox::critical(nullptr, QObject::tr("LOGIN"),
                         QObject::tr("\n username doit etre entre \n"
                                     "4 et 10 characteres"), QMessageBox::Cancel);
             ui->lineEdit_username->setStyleSheet("border: 1px solid red");
         }
       }

       else {

                           QMessageBox::critical(nullptr, QObject::tr("LOGIN"),
                                       QObject::tr("\n remplir les champs avec les informations correctes\n"), QMessageBox::Cancel);
                           ui->lineEdit_username->setStyleSheet("border: 1px solid red" );
                           ui->lineEdit_mdp->setStyleSheet("border: 1px solid red");

       }

}

void MainWindow::on_pushButton_singUp_clicked()
{
        ui->stackedWidget->setCurrentIndex(1);
}

void MainWindow::on_pushButton_enregistrer_clicked()
{
    QString nom=ui->lineEdit_NOM->text();
        QString prenom=ui->lineEdit_PRENOM->text();
        int age=ui->lineEdit_AGE->text().toInt();
        QString username=ui->lineEdit_USERNAME->text();
        QString mdp=ui->lineEdit_MDP->text();
        int telephone=ui->lineEdit_TELEPHONE->text().toInt();
        int n=nom.size();
        int n1=prenom.size();
        int n2=age;
        int n3=username.size();
        int n4=mdp.size();
        int n5=telephone;
        if(n!=0 and n1!=0 and n2!=0 and n3!=0 and n4!=0 and n5!=0)
        {
        login L(nom,prenom,age,username,mdp,telephone);
        bool test =L.ajouter();
        if(test)
        {

            QMessageBox::information(nullptr,QObject::tr("ok"),
                         QObject::tr("Ajout effectue\n"
                                      "click cancel to exit."),QMessageBox::Cancel);
            //notification->show();
               QString titre="Mise a jour";
               QString textMessage="Nouveaux utilisateur ajouter !";
             //  int duree=10000;
               //notification->showMessage(titre,textMessage,QSystemTrayIcon::Information,duree);
            ui->stackedWidget->setCurrentIndex(0);

        }
        else
            QMessageBox::critical(nullptr,QObject::tr("not ok"),
                                  QObject::tr("test vrai\n"
                                              "click cancel to exit."),QMessageBox::Cancel);
    }
        else
        {
            if(n==0)
                ui->lineEdit_NOM->setStyleSheet("border: 1px solid red");
            else
                ui->lineEdit_NOM->setStyleSheet("border: 1px solid green");
            if(n1==0)
                ui->lineEdit_PRENOM->setStyleSheet("border: 1px solid red");
            else
                ui->lineEdit_PRENOM->setStyleSheet("border: 1px solid green");
            if(n2==0)
                ui->lineEdit_AGE->setStyleSheet("border: 1px solid red");
            else
                ui->lineEdit_AGE->setStyleSheet("border: 1px solid green");
            if(n3==0)
                ui->lineEdit_USERNAME->setStyleSheet("border: 1px solid red");
            else
                ui->lineEdit_USERNAME->setStyleSheet("border: 1px solid green");
            if(n4==0)
                ui->lineEdit_MDP->setStyleSheet("border: 1px solid red");
            else
                ui->lineEdit_MDP->setStyleSheet("border: 1px solid green");
            if(n5==0)
                ui->lineEdit_TELEPHONE->setStyleSheet("border: 1px solid red");
            else
                ui->lineEdit_TELEPHONE->setStyleSheet("border: 1px solid green");
        }
}

void MainWindow::on_pb_gestion_finance_clicked()
{
    hide();
    GF = new gestionfinance(this);
    GF->show();

}

void MainWindow::on_pushButton_close_clicked()
{
    close();
}



void MainWindow::on_pb_annuler_Enregistrement_clicked()
{
        ui->stackedWidget->setCurrentIndex(0);
}

void MainWindow::on_pb_gestion_adherents_clicked()
{
    hide();
    GA= new GestionAdherent();
    GA->show();
}

void MainWindow::on_pb_gestion_cours_clicked()
{
    hide();
    GS= new Dialogmain();
    GS->show();
}

void MainWindow::on_pb_gestion_personnel_clicked()
{
    hide();
    GP= new gestionpersonnel();
    GP->show();
}

void MainWindow::on_pb_gestion_sponsors_clicked()
{
    hide();
    GEV= new gestionevenement();
    GEV->show();
}
