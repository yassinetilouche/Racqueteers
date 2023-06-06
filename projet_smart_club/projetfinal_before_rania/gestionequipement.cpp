#include "gestionequipement.h"
#include "mainwindow.h"
#include "ui_gestionequipement.h"
#include "equipement.h"
#include "fournisseur.h"
#include "screenshot.h"
#include "entreprise.h"
#include <QMessageBox>
#include <QIntValidator>
#include <QRegExp>
#include <QRegExpValidator>
#include <QRegularExpression>
#include "stmp.h"
#include <QTimer>
#include "qrcode.h"
#include<QSqlQuery>
#include <QPainter>
#include <QPrinter>
#include <QPrintDialog>
#include <QBrush>
#include <QtWidgets>
#include <QtPrintSupport/qtprintsupportglobal.h>
#include "arduino.h"
#include "exportexcelobjet.h"
#include <QDate>
#include <QDateEdit>
#include "commande.h"
#include <QGraphicsItemAnimation>
#include <QPropertyAnimation>

using namespace qrcodegen;

gestionequipement::gestionequipement(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::gestionequipement)
{ // setBackgroundBrush(QPixmap(":/images/background.jpg"));
    //Player =new QMediaPlayer();
     //Player->setMedia(QUrl("qrc:/click.mp3"));
    //connect(Player,&QMediaPlayer::positionChanged,this,&MainWindow::on_positionChanged);
    //connect(Player,&QMediaPlayer::durationChanged,this,&MainWindow::on_durationChanged);

    ui->setupUi(this);
    QPixmap pix("C:/Users/Yassine/Downloads/tennislogo.png");
    int w =ui->logo->width();
    int h=ui->logo->height();
    ui->logo->setPixmap(pix.scaled(w,h,Qt::KeepAspectRatio));
    int ret=arduino.connect_arduino();
    switch(ret){
    case (0): qDebug() << "arduino is available and connect too:"<<arduino.getarduino_port_name();break;
    case (1): qDebug() << "arduino is available and not connect too:"<<arduino.getarduino_port_name();break;
    case (-1): qDebug() << "arduino is not available:";
    }
    QObject::connect(arduino.getserial(),SIGNAL(readyRead()),this,SLOT(update_label()));


//********************************************parking******************************************************
park(3);
//************************************************controldesaisie***********************************************
    ui->le_id->setValidator(new QIntValidator(1, 9999, this));
    ui->le_id_2->setValidator(new QIntValidator(1, 9999, this));
    ui->le_telephone->setValidator(new QIntValidator(11111111, 99999999, this));
    ui->le_id_supp->setValidator(new QIntValidator(1, 9999, this));
    ui->le_id_supp_f->setValidator(new QIntValidator(1, 9999, this));
    ui->le_id_entreprise->setValidator(new QIntValidator(1, 9999, this));
    ui->le_id_c->setValidator(new QIntValidator(1, 9999, this));
    ui->le_id_supp_c->setValidator(new QIntValidator(1, 9999, this));
    ui->le_id_recherche_c->setValidator(new QIntValidator(1, 9999, this));
    ui->le_cp->setValidator(new QIntValidator(1000, 9999, this));
    ui->le_id_e_supp->setValidator(new QIntValidator(1, 9999, this));
    ui->erreur->setReadOnly(true);
    ui->erreur_f->setReadOnly(true);
    ui->erreur_EN->setReadOnly(true);
    ui->le_nom->setValidator( new QRegExpValidator(QRegExp("[A-Za-z]{1,8}"), this));
    ui->le_prenom->setValidator( new QRegExpValidator(QRegExp("[A-Za-z]{1,8}"), this));
    ui->le_nom_E->setValidator( new QRegExpValidator(QRegExp("[A-Za-z]{1,8}"), this));
    ui->le_rue_E->setValidator( new QRegExpValidator(QRegExp("[A-Za-z]{1,8}"), this));
    //ui->le_email_E->setValidator( new QRegExpValidator(QRegExp("^[0-9a-zA-Z]+([0-9a-zA-Z]*[-._+])*[0-9a-zA-Z]+@[0-9a-zA-Z]+([-.][0-9a-zA-Z]+)*([0-9a-zA-Z]*[.])[a-zA-Z]{2,6}$"), this));
    QRegularExpression rx("\\b[A-Z0-9._%+-]+@[A-Z0-9.-]+\\.[A-Z]{2,4}\\b",
                              QRegularExpression::CaseInsensitiveOption);
        ui->le_email_E->setValidator(new QRegularExpressionValidator(rx, this));
      QString mail=ui->le_email_E->text();
    //    if(rx.match(mail).hasmuch()){}
       // ok=ui->le_email_E->text().contains(rx);

//QRegularExpression maRegex("^[0-9a-zA-Z]+([0-9a-zA-Z][-._+])[0-9a-zA-Z]+@[0-9a-zA-Z]+([-.][0-9a-zA-Z]+)([0-9a-zA-Z][.])[a-zA-Z]{2,6}$");
//emailEdit->setValidator(new QRegularExpressionValidator(rx, this));
//ok=ui->le_email_E->text().contains(maRegex);

Menu();
//ui->tab_equipement->setModel(E.afficher());
ui->tab_fournisseur->setModel(F.afficherf());
ui->tab_entreprise->setModel(EN.afficher());
ui->tab_commande->setModel(c.afficher());

proxyModel= new QSortFilterProxyModel(this);
proxyModel->setSourceModel(E.afficher());
proxyModel->setFilterCaseSensitivity(Qt::CaseInsensitive);
proxyModel->setFilterKeyColumn(-1);
ui->tab_equipement->setModel(proxyModel);
ui->comboBoxfiltre->addItems(QStringList() <<"id_equipement"<<"etat"<<"nombre"<<"type"<<"prix"<<"tous");

QSqlQuery qry=EN.lister();
if(qry.exec())
   {
    while (qry.next()){
   QString nom = qry.value(0).toString();
    ui->le_entreprise->addItem(nom);
    }}

QSqlQuery q=F.lister();
if(qry.exec())
   {
    while (q.next()){
   QString idf = q.value(0).toString();
    ui->le_id_f_c->addItem(idf);
    }}


QSqlQuery query=E.lister("Non");
if(query.exec())
   {
    while (query.next()){
   QString idf = query.value(0).toString();
    ui->le_id_eq_c->addItem(idf);
    }}

//*********************************STATISTIQUES*********************************************
    QBarSet *set0= new QBarSet("Ancien");
    QBarSet *set1= new QBarSet("nouveau");
        *set0 << E.recherche("Ancien","Chaussures")<< E.recherche("Ancien","Raquette")<<E.recherche("Ancien","Balles");
        *set1 << E.recherche("Nouveau","Chaussures")<< E.recherche("Nouveau","Raquette")<< E.recherche("Nouveau","Balles");

       QBarSeries *series= new QBarSeries();
       series->append(set0);
       series->append(set1);
       QChart *chart =new QChart ;
        chart->addSeries(series);
        chart->setTitle("Nombres total des équipements");
        chart->createDefaultAxes();
        chart->setAnimationOptions(QChart::AllAnimations);

        QStringList cat;
        cat <<"chausseurs"<<"raquettes"<<"balles";
        QBarCategoryAxis *axis =new QBarCategoryAxis();
        axis->append(cat);
        chart->createDefaultAxes();
        chart->setAxisX(axis,series);

        chart->legend()->setVisible(true);
        chart->legend()->setAlignment(Qt::AlignBottom);
        QChartView *chartView = new QChartView(chart);
        chartView->setRenderHint(QPainter::Antialiasing);
        chartView->resize(500,300);
        chartView->setParent(ui->statv);

}


gestionequipement::~gestionequipement()
{
    delete ui;
}

//********************************arduino*****************************

void gestionequipement::park(int etat_voiture)
{//int i=-1;
    scene= new QGraphicsScene();
    ui->parking->setScene(scene);
    QBrush redBrush(Qt::red);
    QBrush grayBrush(Qt::gray);
    QBrush greenBrush(Qt::green);
    QBrush whiteBrush(Qt::white);

    QPen blackPen(Qt::black);
    QPen greenPen(Qt::Key_Green);
    blackPen.setWidth(2);
    Rectangle1=scene->addRect(-100,-100,70,90,greenPen,grayBrush);
    Rectangle2=scene->addRect(-200,-100,70,90,greenPen,grayBrush);
    Rectangle3=scene->addRect(-300,-100,70,90,greenPen,grayBrush);
    Rectangle4=scene->addRect(-400,-100,70,90,greenPen,grayBrush);

    Rectangle5=scene->addRect(-100,-250,70,90,greenPen,grayBrush);
    Rectangle6=scene->addRect(-200,-250,70,90,greenPen,grayBrush);
    Rectangle7=scene->addRect(-300,-250,70,90,greenPen,grayBrush);
    Rectangle8=scene->addRect(-400,-250,70,90,greenPen,grayBrush);

  //  i=update_label();//0bl 1v 2r
    if(etat_voiture==0){Rectangle1=scene->addRect(-100,-100,70,90,greenPen,whiteBrush);
    ui->le_n_places->setText("voiture en train de se garée");}
    if(etat_voiture==1){Rectangle1=scene->addRect(-100,-100,70,90,greenPen,greenBrush);
    ui->le_n_places->setText("voiture est bien garée");}
    if(etat_voiture==2){Rectangle1=scene->addRect(-100,-100,70,90,greenPen,redBrush);
    ui->le_n_places->setText("voiture mal garée");}
}
int gestionequipement::update_label()
{int i=-1;
    data=arduino.read_from_arduino();
    scene= new QGraphicsScene();
    ui->parking->setScene(scene);
    QBrush redBrush(Qt::red);
    QBrush grayBrush(Qt::gray);
    QBrush greenBrush(Qt::green);
    QBrush whiteBrush(Qt::white);

    QPen blackPen(Qt::black);
    QPen greenPen(Qt::Key_Green);
    blackPen.setWidth(2);
    Rectangle1=scene->addRect(-100,-100,70,90,greenPen,grayBrush);
    Rectangle2=scene->addRect(-200,-100,70,90,greenPen,grayBrush);
    Rectangle3=scene->addRect(-300,-100,70,90,greenPen,grayBrush);
    Rectangle4=scene->addRect(-400,-100,70,90,greenPen,grayBrush);

    Rectangle5=scene->addRect(-100,-250,70,90,greenPen,grayBrush);
    Rectangle6=scene->addRect(-200,-250,70,90,greenPen,grayBrush);
    Rectangle7=scene->addRect(-300,-250,70,90,greenPen,grayBrush);
    Rectangle8=scene->addRect(-400,-250,70,90,greenPen,grayBrush);

    if(data=="0"){ui->le_n_places->setText("la voiture est trop loin du capteur"); i=0;Rectangle1=scene->addRect(-100,-100,70,90,greenPen,whiteBrush);}//blanche
    if(data=="1"){ui->le_n_places->setText("La voiture est dans la bonne zone ");i=1;Rectangle1=scene->addRect(-100,-100,70,90,greenPen,greenBrush);}//vert
    if(data=="2"){ui->le_n_places->setText("La voiture est trop proche du capture");i=2;Rectangle1=scene->addRect(-100,-100,70,90,greenPen,redBrush);}//rouge

return i;}
//******************************table EQUIPEMENT************************************

void gestionequipement::on_pb_ajouter_clicked()
{//Player =new QMediaPlayer();
   // Player->setMedia(QUrl("qrc:/click.mp3"));
   // Player->play();
    int k=0;
    ui->erreur->clear();
    int id_equipement=ui->le_id->text().toInt();
    QString etat=ui->le_etat->currentText();
    int nombre=ui->le_nombre->text().toInt();
    QString type=ui->le_type->currentText();
    float prix=ui->le_prix->text().toInt();
    QString disponibilite=ui->le_dispo->currentText();
   Equipement E(id_equipement,etat,nombre,type,prix,disponibilite);
QStringList test=E.ajouter();
if(test.length()==0){ ui->erreur->clear();ui->erreur->setText(("Echec d'e modification'ajout suit a un probleme a la base"));}
else{
    {for(k=0;k<test.length();k++)
      {ui->erreur->append(test.at(k));
     ui->tab_equipement->setModel(E.charger());}
        }}
connect(timer,SIGNAL(timeout()),this,SLOT(timere()));
timer->start(5000);
}

void gestionequipement::on_pb_supprimer_clicked()
{Equipement E1; E1.setid_equipement(ui->le_id_supp->text().toInt());
    bool test=E1.supprimer(E1.getid_equipement());
    QMessageBox msgBox;
    if(test)
       { msgBox.setText("Suppression avec succes.");
        ui->tab_equipement->setModel(E.charger());
       }
    else
        msgBox.setText("Echec de suppression");
        msgBox.exec();
}

void gestionequipement::on_pb_changer_clicked()
{int k=0;
     ui->erreur->clear();
    int id_equipement=ui->le_id->text().toInt();
    QString etat=ui->le_etat->currentText();
    int nombre=ui->le_nombre->text().toInt();
    QString type=ui->le_type->currentText();
    float prix=ui->le_prix->text().toInt();
    QString disponibilite=ui->le_dispo->currentText();
   Equipement E(id_equipement,etat,nombre,type,prix,disponibilite);

QStringList test=E.changer();
if(test.length()==0){ ui->erreur->clear();ui->erreur->setText(("Echec de modification suit a un probleme a la base"));}
else{
    for(k=0;k<test.length();k++)
     { ui->erreur->append(test.at(k));
         ui->tab_equipement->setModel(E.charger());}}
connect(timer,SIGNAL(timeout()),this,SLOT(timere()));
timer->start(5000);
}

void gestionequipement::on_pb_charger_clicked()
{
   Equipement E2;
   ui->tab_equipement->setModel(E2.charger());
}

void gestionequipement::on_pb_trier_clicked()
{
    Equipement E2;
    ui->tab_equipement->setModel(E2.trier());
}

void gestionequipement::on_pb_pfd_clicked()
{Equipement E4;
    QPrinter printer;
    printer.setOutputFormat(QPrinter::PdfFormat);
    printer.setOutputFileName("equipement.pdf");
    QPainter painter;
    if(!painter.begin(&printer)){
        qWarning("failed to open");}
        QSqlQuery qry=E4.lister();
    if(qry.exec())
        {while (qry.next()){
        QString n = qry.value(0).toString();
        QString d = qry.value(1).toString();
        QString e = qry.value(2).toString();
        QString f = qry.value(3).toString();
        QString g = qry.value(4).toString();
    printer.setPageSize(QPrinter::A4);
    painter.setPen(Qt::blue);
    painter.setFont(QFont("Times",30));
        painter.drawText(200,100,"Fiche Des Equipements");
        painter.drawPixmap(QRect(10,10,80,80),QPixmap("C:/Atelier_Connexion-20210307T163152Z-001/build-Atelier_Connexion-Desktop_Qt_5_9_9_MinGW_32bit-Debug/logo.jpg"));
        painter.setFont(QFont("Times",15));
        painter.setPen(Qt::black);
        painter.drawText(100,200,"L'identifiant de l'équipement");
        painter.drawText(100,300,"L'état de l'équipement");
        painter.drawText(100,400,"Le nombre de pièces");
        painter.drawText(100,500,"Le type de l'équiment");
        painter.drawText(100,600,"Le prix par pièces");
        painter.drawText(400,200,n);
        painter.drawText(400,300,d);
        painter.drawText(400,400,e);
        painter.drawText(400,500,f);
        painter.drawText(400,600,g+" Dt");
        printer.newPage();
    }
    }
      painter.end();
    }
//****************************************arduino***************************************************

void gestionequipement::on_pb_rechercher_clicked()
{Equipement E3;
    QString eta= ui->le_id_r->text();
    ui->tab_equipement->setModel(E3.rechercher(eta));
}
//******************************************tab_equipement******************************************

void gestionequipement::on_tab_equipement_activated(const QModelIndex &index)
{
    QString val=ui->tab_equipement->model()->data(index).toString();
    QSqlQuery qry;
    qry.prepare("select * from equipement where  id_equipement='"+val+"'");
    if(qry.exec())
        {while(qry.next())
            {
                ui->le_id->setText(qry.value(0).toString());
                ui->le_id_supp->setText(qry.value(0).toString());
                ui->le_id_r->setText(qry.value(0).toString());
                ui->le_etat->setCurrentText(qry.value(1).toString());
                ui->le_nombre->setValue(qry.value(2).toInt());
                ui->le_type->setCurrentText(qry.value(3).toString());
                ui->le_prix->setValue(qry.value(4).toFloat());
                ui->le_dispo->setCurrentText(qry.value(5).toString());
            }
        }
    else {
        QMessageBox::critical(nullptr, QObject::tr("fournisseur"),
                    QObject::tr("Erreur !\n"
                                "Click Cancel to exit."), QMessageBox::Cancel);
    }

}

//********************************tab FOURNISSEURS*************************************

void gestionequipement::on_pb_supprimer_f_clicked()
{Fournisseur F1; F1.setid_fournisseur(ui->le_id_supp_f->text().toInt());
    bool test=F1.supprimerf(F1.getid_fournisseur());
    QMessageBox msgBox;
    if(test)
       { msgBox.setText("Suppression avec succes.");
        ui->tab_fournisseur->setModel(F.afficherf());
       }
    else
        msgBox.setText("Echec de suppression");
        msgBox.exec();

}

void gestionequipement::on_pb_changer_f_clicked()
{int k=0;
      ui->erreur_f->clear();
    int id_fournisseur=ui->le_id_2->text().toInt();
    int telephone=ui->le_telephone->text().toInt();
    QString nom=ui->le_nom->text();
    QString prenom=ui->le_prenom->text();
    QString entreprise=ui->le_entreprise->currentText();
    float facture=ui->le_facture->text().toFloat();

    Fournisseur F(id_fournisseur,telephone,facture,nom,prenom,entreprise);

    QStringList test=F.changerf();
    if(test.length()==0){ ui->erreur_f->clear();ui->erreur_f->setText("erreur");}
    else if(test.length()==1){ ui->erreur_f->clear(); ui->erreur_f->append(test.at(k));
                                ui->tab_fournisseur->setModel(F.afficherf());}
    else if(test.length()>1)
    {for(k=0;k<test.length();k++)
          ui->erreur_f->append(test.at(k));
    }
    connect(timer,SIGNAL(timeout()),this,SLOT(timere()));
    timer->start(5000);
 }

void gestionequipement::on_pb_ajoute_f_clicked()
{   int k=0;
    ui->erreur_f->clear();
    int id_fournisseur=ui->le_id_2->text().toInt();
     int telephone=ui->le_telephone->text().toInt();
      QString nom=ui->le_nom->text();
      QString prenom=ui->le_prenom->text();
      QString entreprise=ui->le_entreprise->currentText();
     float facture=ui->le_facture->text().toFloat();
     Fournisseur F(id_fournisseur,telephone,facture,nom,prenom,entreprise);

     QStringList test=F.ajouterf();
     if(test.length()==0){ ui->erreur_f->clear();ui->erreur_f->setText("erreur d'ajout a la base de donnée");}
     else if(test.length()==1){ ui->erreur_f->clear(); ui->erreur_f->append(test.at(k));
         ui->tab_fournisseur->setModel(F.afficherf());}
     else if(test.length()>1)
     {for(k=0;k<test.length();k++)
         {  ui->erreur_f->append(test.at(k));}}
     connect(timer,SIGNAL(timeout()),this,SLOT(timere()));
     timer->start(5000);
     }

void gestionequipement::on_pb_pfd_f_clicked()
{Fournisseur F4;
    QPrinter printer;
    printer.setOutputFormat(QPrinter::PdfFormat);
    printer.setOutputFileName("C:/Users/Yassine/Desktop/fichiervalidation3/fournisseur.pdf");
    QPainter painter;
    if(!painter.begin(&printer)){
        qWarning("failed to open");}
        QSqlQuery qry=F4.lister_f();

            QDate date = QDate::currentDate();
            QString dat = date.toString("dd.MM.yyyy");

        printer.setPageSize(QPrinter::A4);
        printer.setPageMargins(QMarginsF(15, 15, 15, 15));
        painter.setPen(Qt::white);
        painter.setFont(QFont("Times",40));
        painter.drawPixmap(QRect(10,30,750,100),QPixmap("C:/Users/Yassine/Downloads/raniia-20210507T060557Z-001/raniia/rec.jpg"));
        painter.drawPixmap(QRect(10,1020,750,70),QPixmap("C:/Users/Yassine/Downloads/raniia-20210507T060557Z-001/raniia/rec.jpg"));
        painter.drawPixmap(QRect(50,1020,70,70),QPixmap("C:/Users/Yassine/Downloads/raniia-20210507T060557Z-001/raniia/logo1.png"));
        painter.drawPixmap(QRect(150,1020,70,70),QPixmap("C:/Users/Yassine/Downloads/raniia-20210507T060557Z-001/raniia/logo2.png"));
        painter.drawPixmap(QRect(250,1020,70,70),QPixmap("C:/Users/Yassine/Downloads/raniia-20210507T060557Z-001/raniia/logo3.png"));
        painter.drawPixmap(QRect(350,1020,70,70),QPixmap("C:/Users/Yassine/Downloads/raniia-20210507T060557Z-001/raniia/logo4.png"));
        painter.drawPixmap(QRect(450,1020,70,70),QPixmap("C:/Users/Yassine/Downloads/raniia-20210507T060557Z-001/raniia//logo5.png"));
        painter.drawPixmap(QRect(550,1020,70,70),QPixmap("C:/Users/Yassine/Downloads/raniia-20210507T060557Z-001/raniia//logo6.png"));


        painter.drawPixmap(QRect(30,130,700,850),QPixmap("C:/Users/Yassine/Downloads/raniia-20210507T060557Z-001/raniia/tennis07.jpg"));
        painter.drawText(130,100,"Liste des Fournisseurs");
        painter.drawPixmap(QRect(10,10,80,80),QPixmap("C:/Users/Yassine/Downloads/raniia-20210507T060557Z-001/raniia/logo.jpg"));
        painter.setFont(QFont("Times",15));
        painter.setPen(Qt::black);
         //painter.fillRect(100,150,600,600,40500);
        painter.drawText(10,10,dat);
        painter.drawText(100,200,"L'id");
                painter.drawText(150,200,"Téléphone");
                painter.drawText(300,200,"Facture");
                painter.drawText(400,200,"nom");
                painter.drawText(500,200,"prenom");
                painter.drawText(600,200,"entreprise");
                painter.drawLine(80,250,700,250);
                int i=0;
                if(qry.exec())
                    {while (qry.next()){
                    QString id = qry.value(0).toString();
                    QString tel = qry.value(1).toString();
                    QString fact = qry.value(2).toString();
                    QString nom= qry.value(3).toString();
                     QString pre = qry.value(4).toString();
                    QString entrep = qry.value(5).toString();

                painter.drawText(100,300+i,id);
                painter.drawText(150,300+i,tel);
                painter.drawText(300,300+i,fact+" Dt");
                painter.drawText(400,300+i,nom);
                painter.drawText(500,300+i,pre);
                painter.drawText(600,300+i,entrep);
                //painter.drawRect(100,150,600,600);
                painter.drawLine(80,350+i,700,350+i);
                i=100+i;


    }
    }
      painter.end();
    }

void gestionequipement::on_tab_fournisseur_activated(const QModelIndex &index)
{
    QString val=ui->tab_fournisseur->model()->data(index).toString();
    QSqlQuery qry;
    qry.prepare("select * from fournisseur where  id_fournisseur='"+val+"' or nom='"+val+"' or prenom='"+val+"' or entreprise='"+val+"'");
    if(qry.exec())
        {while(qry.next())
            {
                ui->le_id_2->setText(qry.value(0).toString());

                ui->le_id_supp_f->setText(qry.value(0).toString());
                ui->le_telephone->setText(qry.value(1).toString());
                ui->le_facture->setText(qry.value(2).toString());
                ui->le_nom->setText(qry.value(3).toString());
                  ui->le_prenom->setText(qry.value(4).toString());
                ui->le_entreprise->setCurrentText(qry.value(5).toString());
            }
        }
    else {
        QMessageBox::critical(nullptr, QObject::tr("fournisseur"),
                    QObject::tr("Erreur !\n"
                                "Click Cancel to exit."), QMessageBox::Cancel);
    }
}

void gestionequipement::on_pb_imprime_pdf_clicked()
{QPrinter printer;
    printer.setPrinterName("fournisseur");
    QPrintDialog dialog(&printer,this);
    if (dialog.exec() == QDialog::Rejected) return;
    ui->tab_fournisseur->render(&printer);
}

void gestionequipement::on_pb_afficher_f_clicked()
{Fournisseur F2;
    ui->tab_fournisseur->setModel(F2.afficher_f());
}


//*******************************METIERS******************************************************

void gestionequipement::on_pb_screenshott_clicked()
{
          s.show();
}

//void MainWindow::resizeEvent(QResizeEvent * /* event */)
/*{
    QSize scaledSize = originalPixmap.size();
    scaledSize.scale(ui->tabWidget->size(), Qt::KeepAspectRatio);
    ui->tabWidget->setPixmap(originalPixmap.scaled(ui->tabWidget->size(),
                                                     Qt::KeepAspectRatio,
                                                     Qt::SmoothTransformation));

}*/

void gestionequipement::Menu()
{
    QMenu *fileMenu = menuBar()->addMenu(tr("&File"));
    QAction *openAct = fileMenu->addAction(tr("&capture ecran"), this, &gestionequipement::on_pb_screenshott_clicked);
    openAct->setShortcuts(QKeySequence::Open);

    QAction *exitAct = fileMenu->addAction(tr("E&xit"), this, &QWidget::close);
    exitAct->setShortcuts(QKeySequence::Quit);
    //menuBar()->addSeparator();
}



void gestionequipement::on_le_filtre_textChanged(const QString &arg1)
{
    proxyModel->setFilterFixedString(arg1);
}

void gestionequipement::on_comboBoxfiltre_currentIndexChanged(int index)
{
    if(index==5){
        index=-1;
    }
    proxyModel->setFilterKeyColumn(index);
}

//*****************Entreprise*************************************************************************************

void gestionequipement::on_pb_ajoute_e_clicked()
{   int k=0;
      ui->erreur_EN->clear();
 int id_entreprise=ui->le_id_entreprise->text().toInt();
         QString nom=ui->le_nom_E->text();
         QString ville=ui->le_ville->currentText();
        QDate date_colab=ui->le_date_E->date();
         QString rue=ui->le_rue_E->text();
          int code_postal=ui->le_cp->text().toInt();
          QString email=ui->le_email_E->text();

          if(ui->le_email_E->text() != "")
              {
                  QRegExp mailREX("\\b[A-Z0-9._%+-]+@[A-Z0-9.-]+\\.[A-Z]{2,4}\\b");
                  mailREX.setCaseSensitivity(Qt::CaseInsensitive);
                  mailREX.setPatternSyntax(QRegExp::RegExp);
                  qDebug() << mailREX.exactMatch("me@me.com");

                  if(!mailREX.exactMatch(ui->le_email_E->text()))
                  {

                      QPropertyAnimation* anim = new QPropertyAnimation(ui->emailWarning, "geometry");
                      anim->setDuration(500);
                      anim->setEasingCurve(QEasingCurve::InOutSine);
                      anim->setStartValue(QRect(ui->emailWarning->geometry().x()+5,ui->emailWarning->geometry().y(),ui->emailWarning->geometry().width(),ui->emailWarning->geometry().height()));
                      anim->setEndValue(QRect(ui->emailWarning->geometry().x(),ui->emailWarning->geometry().y(),ui->emailWarning->geometry().width(),ui->emailWarning->geometry().height()));
                      anim->start();
                     //animateObjWhite(ui->le_email_E,255);
                      ui->emailWarning->setText("<font color='red'>Mauvaise Email</font>");

                      return;
                  }


                  ui->emailWarning->setText("");
              }

        Entreprise EN(id_entreprise,nom,ville,rue,code_postal,email,date_colab);

        QStringList test=EN.ajouter();
        if(test.length()==0){ ui->erreur_EN->clear();ui->erreur_EN->setText("erreur d'ajout a la base de donnée");}
        else if(test.length()==1){ ui->erreur_EN->clear(); ui->erreur_EN->append(test.at(k));
            ui->tab_entreprise->setModel(EN.charger());}
        else if(test.length()>1)
        {for(k=0;k<test.length();k++)
            {  ui->erreur_EN->append(test.at(k));}}


        connect(timer,SIGNAL(timeout()),this,SLOT(timere()));
        timer->start(5000);

}

void gestionequipement::timere(){
     ui->erreur_EN->clear();
     ui->erreur_c->clear();
     ui->erreur_f->clear();
     ui->erreur->clear();
}

void gestionequipement::on_pb_changer_e_clicked()
{int k=0;ok=true;
      ui->erreur_EN->clear();
    int id_entreprise=ui->le_id_entreprise->text().toInt();
             QString nom=ui->le_nom_E->text();
             QString ville=ui->le_ville->currentText();
            QDate date_colab=ui->le_date_E->date();
             QString rue=ui->le_rue_E->text();
              int code_postal=ui->le_cp->text().toInt();
              QString email=ui->le_email_E->text();

              if(ui->le_email_E->text() != "")
                  {
                      QRegExp mailREX("\\b[A-Z0-9._%+-]+@[A-Z0-9.-]+\\.[A-Z]{2,4}\\b");
                      mailREX.setCaseSensitivity(Qt::CaseInsensitive);
                      mailREX.setPatternSyntax(QRegExp::RegExp);
                      qDebug() << mailREX.exactMatch("me@me.com");

                      if(!mailREX.exactMatch(ui->le_email_E->text()))
                      {

                          QPropertyAnimation* anim = new QPropertyAnimation(ui->emailWarning, "geometry");
                          anim->setDuration(500);
                          anim->setEasingCurve(QEasingCurve::InOutSine);
                          anim->setStartValue(QRect(ui->emailWarning->geometry().x()+5,ui->emailWarning->geometry().y(),ui->emailWarning->geometry().width(),ui->emailWarning->geometry().height()));
                          anim->setEndValue(QRect(ui->emailWarning->geometry().x(),ui->emailWarning->geometry().y(),ui->emailWarning->geometry().width(),ui->emailWarning->geometry().height()));
                          anim->start();
                         //animateObjWhite(ui->le_email_E,255);
                          ui->emailWarning->setText("<font color='red'>Mauvaise Email</font>");

                          return;
                      }
              }

            Entreprise EN(id_entreprise,nom,ville,rue,code_postal,email,date_colab);

            QStringList test=EN.modifier();
            if(test.length()==0){ ui->erreur_EN->clear();ui->erreur_EN->setText("erreur de modification lié la base de donnée");}
            else if(test.length()==1){ ui->erreur_EN->clear(); ui->erreur_EN->append(test.at(k));
                ui->tab_entreprise->setModel(EN.charger());}
            else if(test.length()>1)
            {for(k=0;k<test.length();k++)
                {  ui->erreur_EN->append(test.at(k));}}

            connect(timer,SIGNAL(timeout()),this,SLOT(timere()));
            timer->start(5000);

    }





void gestionequipement::on_tab_entreprise_activated(const QModelIndex &index)
{
    QString val=ui->tab_entreprise->model()->data(index).toString();
    QSqlQuery qry;
    qry.prepare("select * from entreprise where  id_entreprise='"+val+"'");
    if(qry.exec())
        {while(qry.next())
            {
                ui->le_id_entreprise->setText(qry.value(0).toString());
                ui->le_id_e_recherche->setText(qry.value(0).toString());
                ui->le_id_e_supp->setText(qry.value(0).toString());
                ui->le_nom_E->setText(qry.value(1).toString());
              ui->le_ville->setCurrentText(qry.value(2).toString());
              ui->le_rue_E->setText(qry.value(3).toString());
             ui->le_cp->setText(qry.value(4).toString());
             ui->le_email_E->setText(qry.value(5).toString());
              ui->le_date_E->setDate(qry.value(6).toDate());

            }
        }
    else {
        QMessageBox::critical(nullptr, QObject::tr("entreprise"),
                    QObject::tr("Erreur !\n"
                                "Click Cancel to exit."), QMessageBox::Cancel);
    }
}

void gestionequipement::on_pb_afficher_e_clicked()
{
       ui->tab_entreprise->setModel(EN.charger());
}


void gestionequipement::on_pb_supprimer_e_clicked()
{
    Entreprise EN1; EN1.setid_entreprise(ui->le_id_e_supp->text().toInt());
        bool test=EN1.supprimer(EN1.getid_entreprise());
        QMessageBox msgBox;
        if(test)
           { msgBox.setText("Suppression avec succes.");
            ui->tab_entreprise->setModel(EN1.afficher());
           }
        else
            msgBox.setText("Echec de suppression");
            msgBox.exec();
}

void gestionequipement::on_pb_rechercher_e_clicked()
{Entreprise EN1;
    QString val= ui->le_id_e_recherche->text();
    ui->tab_entreprise->setModel(EN1.rechercher(val));

}

void gestionequipement::on_pb_trier_e_clicked()
{
        Entreprise EN2;
        ui->tab_entreprise->setModel(EN2.trier());
}

//*****************************googlesearch***********************************************


void gestionequipement::on_pb_search_clicked()
{
    searchEdit.show();
}

//***************************mailing********************************************************


void gestionequipement::on_pb_email_clicked()
{ Smtp* smtp;

       smtp = new Smtp("tennisclub@gmail.com", "tennis2021", "smtp.gmail.com");

       smtp->sendMail(ui->le_email_E->text(),ui->le_email_E->text(), "tennis club",ui->le_emailtext->text());

}
//*******************************excel*******************************************************
void gestionequipement::on_pb_excel_clicked()
{
    QString fileName = QFileDialog::getSaveFileName(this, tr("Exportation en fichier Excel"), qApp->applicationDirPath (),
                                                            tr("Fichiers d'extension Excel (*.xls)"));
            if (fileName.isEmpty())
                return;

            ExportExcelObject obj(fileName, "mydata", ui->tab_fournisseur);


            obj.addField(0, "id_fournisseur", "char(20)");
            obj.addField(1, "telephone", "char(20)");
            obj.addField(2, "facture", "char(20)");
            obj.addField(3, "nom", "char(20)");
            obj.addField(4, "prenom", "char(20)");
            obj.addField(5, "entreprise", "char(20)");


            int retVal = obj.export2Excel();

            if( retVal > 0)
            {
                QMessageBox::information(this, tr("FAIS!"),
                                         QString(tr("%1 enregistrements exportés!")).arg(retVal)
                                         );
            }

}
//**************************************parking****************************************************************


/*
void gestionequipement::on_pb_etat_voiture_clicked()
{

    park(ui->le_etat_voiture->text().toInt());

}
*/
//***********************************************commande******************************************************


void gestionequipement::on_pb_ajoute_c_clicked()
{   int k=0;
      ui->erreur_c->clear();
 int id_commande=ui->le_id_c->text().toInt();
 QDate date_commande=ui->le_date_c->date();
 int id_f=ui->le_id_f_c->currentText().toInt();
 QString type_commande=ui->le_type_c->currentText();
 int id_eq=ui->le_id_eq_c->currentText().toInt();

        commande c(id_commande,date_commande,id_f,type_commande,id_eq);

        QStringList test=c.ajouter();
        if(test.length()==0){ ui->erreur_c->clear();ui->erreur_c->setText("erreur d'ajout a la base de donnée");}
        else if(test.length()==1){ ui->erreur_c->clear(); ui->erreur_c->append(test.at(k));
            ui->tab_commande->setModel(c.charger());}
        else if(test.length()>1)
        {for(k=0;k<test.length();k++)
            {  ui->erreur_c->append(test.at(k));}}

        connect(timer,SIGNAL(timeout()),this,SLOT(timere()));
        timer->start(5000);

}


void gestionequipement::on_pb_changer_c_clicked()
{int k=0;ok=true;
      ui->erreur_c->clear();
      int id_commande=ui->le_id_c->text().toInt();
      QDate date_commande=ui->le_date_c->date();
      int id_f=ui->le_id_f_c->currentText().toInt();
      QString type_commande=ui->le_type_c->currentText();
      int id_eq=ui->le_id_eq_c->currentText().toInt();

             commande c(id_commande,date_commande,id_f,type_commande,id_eq);

            QStringList test=c.modifier();
            if(test.length()==0){ ui->erreur_c->clear();ui->erreur_c->setText("erreur de modification lié la base de donnée");}
            else if(test.length()==1){ ui->erreur_c->clear(); ui->erreur_c->append(test.at(k));
                ui->tab_commande->setModel(c.charger());}
            else if(test.length()>1)
            {for(k=0;k<test.length();k++)
                {  ui->erreur_c->append(test.at(k));}}
            connect(timer,SIGNAL(timeout()),this,SLOT(timere()));
            timer->start(5000);
}



void gestionequipement::on_tab_commande_activated(const QModelIndex &index)
{
    QString val=ui->tab_commande->model()->data(index).toString();
    QSqlQuery qry;
    qry.prepare("select * from commande where  id_commande='"+val+"'");
    if(qry.exec())
        {while(qry.next())
            {
                ui->le_id_c->setText(qry.value(0).toString());
                ui->le_id_recherche_c->setText(qry.value(0).toString());
                ui->le_id_supp_c->setText(qry.value(0).toString());
                ui->le_date_c->setDate(qry.value(1).toDate());
                ui->le_id_f_c->setCurrentText(qry.value(2).toString());
                ui->le_type_c->setCurrentText(qry.value(3).toString());
                ui->le_id_eq_c->setCurrentText(qry.value(4).toString());


            }
        }
    else {
        QMessageBox::critical(nullptr, QObject::tr("entreprise"),
                    QObject::tr("Erreur !\n"
                                "Click Cancel to exit."), QMessageBox::Cancel);
    }
}

void gestionequipement::on_pb_afficher_c_clicked()
{
       ui->tab_commande->setModel(c.charger());
}


void gestionequipement::on_pb_supprimer_c_clicked()
{
    commande co; co.setid_commande(ui->le_id_supp_c->text().toInt());
        bool test=co.supprimer(co.getid_commande());
        QMessageBox msgBox;
        if(test)
           { msgBox.setText("Suppression avec succes.");
            ui->tab_commande->setModel(co.afficher());
           }
        else
            msgBox.setText("Echec de suppression");
            msgBox.exec();
}

void gestionequipement::on_pb_rechercher_c_clicked()
{commande co;
    QString val= ui->le_id_recherche_c->text();
    ui->tab_commande->setModel(co.rechercher(val));

}

void gestionequipement::on_pb_trier_c_clicked()
{
        commande co;
        ui->tab_commande->setModel(co.trier());
}

//-**************************************************QRcode*********************************************************

void gestionequipement::on_pb_QrCode_clicked()
{
    int tabev=ui->tab_equipement->currentIndex().row();
        QVariant idd=ui->tab_equipement->model()->data(ui->tab_equipement->model()->index(tabev,0));
        QString id_eqi= idd.toString();
        QSqlQuery qry;
        qry.prepare("select * from equipement where id_equipement=:id_equipement");
        qry.bindValue(":id_equipement", id_eqi);
        qry.exec();
        QString etats,nomb,typ,pri,dispo,ids;
        while(qry.next()){
            etats=qry.value(1).toString();
            nomb=qry.value(2).toString();
            pri=qry.value(3).toString();
            dispo=qry.value(4).toString();

        }
        ids=QString( id_eqi);
        ids="ID: "+ids+" etat: "+etats+"nombre: "+nomb+"prix: "+pri+"disponibilite: "+dispo;
        QrCode qr = QrCode::encodeText(ids.toUtf8().constData(), QrCode::Ecc::HIGH);

        QImage im(qr.getSize(),qr.getSize(), QImage::Format_RGB888);
        for (int y = 0; y < qr.getSize(); y++) {
            for (int x = 0; x < qr.getSize(); x++) {
                int color = qr.getModule(x, y);  // 0 for white, 1 for black

                if(color==0)
                    im.setPixel(x, y,qRgb(254, 254, 254));
                else
                    im.setPixel(x, y,qRgb(0, 0, 0));
            }
        }
        im=im.scaled(100,100);
        ui->QrCode->setPixmap(QPixmap::fromImage(im));
        int i=0 ;
        for(i=0;i<100;i=i+0.1){
            i++;
        }
}



void gestionequipement::on_retour_eq_clicked()
{
    hide();
    Re = new MainWindow(this);
    Re->show();
}
