#include "gestionfinance.h"
#include "ui_gestionfinance.h"
#include "finance.h"
#include <QSqlQueryModel>
#include <QMessageBox>
#include <QDate>
#include <QSqlQuery>
#include "abonnemet.h"
#include "QPainter"
#include "QPdfWriter"
#include "QDesktopServices"
#include "QtPrintSupport/QPrinter"
#include "exportexcelobjet.h"
#include <QFileDialog>
#include "login.h"
#include"qrcode.h"
#include <QString>
#include<vector>
#include<QImageWriter>
#include<QImageReader>
#include<QIntValidator>
#include "mainwindow.h"

#include"stmp.h"



using namespace qrcodegen;
const QString getIniPath2()
{
    const static QString iniPath( qApp->applicationDirPath() + "/settings.ini" );
    return iniPath;
}
QString saveFormats2()
{
    static QString suffix;
    foreach ( const QByteArray & format , QImageWriter::supportedImageFormats() )
        suffix += QString( "%1 ( *.%2 )\n" )
                .arg( QString( format ).toUpper() )
                .arg( QString( format ) );

    return suffix;
}
gestionfinance::gestionfinance(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::gestionfinance)

{
    ui->setupUi(this);
    ui->tab_finance_2->setModel(F.afficher());
    ui->table_abonnement_2->setModel(A.afficher());
     notification = new QSystemTrayIcon(this) ;
     int ret=Ar.connect_arduino(); // lancer la connexion à arduino
         switch(ret){
         case(0):qDebug()<< "arduino is available and connected to : "<< Ar.getarduino_port_name();
             break;
         case(1):qDebug() << "arduino is available but not connected to :" <<Ar.getarduino_port_name();
            break;
         case(-1):qDebug() << "arduino is not available";
         }
}
gestionfinance::~gestionfinance()
{
    delete ui;
}
void gestionfinance::arduinoo()
{
    int x=1;
    if(x==0)
     Ar.write_to_arduino("0");
    else
        Ar.write_to_arduino("1");
}

void gestionfinance::on_pushButton_2_clicked()
{
    int id=ui->id_2->text().toInt();
    QString type=ui->type_2->text();
    QString date=ui->date_2->text();
    float prix=ui->prix_2->text().toInt();
    QString description=ui->description_2->text();
    int n= id;
    int n1=type.size();
    int n2=date.size();
    int n3=prix;
    int n4=description.size();
    if((n!=0 and n1!=0 and n2!=0 and n3!=0 and n4!=0))
    {
         ui->label_erreur->setText("tous les champs remplir");
    finance F(id,type,date,description,prix);

    bool test=F.ajouter();
    if(test)
    {
        //QMessageBox::information(nullptr, QObject::tr("ok"),QObject::tr("Ajout effectué.\n click OK to exit."),QMessageBox::Ok);
        ui->label_erreur->setText("ajout effectué");
    }
    else
        ui->label_erreur->setText("ajout non effectue\n");

     ui->tab_finance_2->setModel(F.afficher());
    }
    else
    {
        if(n==0)
        {
          ui->id_2->setStyleSheet("border: 1px solid red");
          ui->label_erreur->setText("remplir le champ id avec number");
        }
        if(n1==0)
        {
           ui->type_2->setStyleSheet("border: 1px solid red");
           ui->label_erreur->setText("remplir le champ type");
        }
        if(n2==0)
        {
            ui->date_2->setStyleSheet("border: 1px solid red");
            ui->label_erreur->setText("remplir le champ date");
        }
        if(n3==0)
        {
            ui->prix_2->setStyleSheet("border: 1px solid red");
             ui->label_erreur->setText("remplir le champ prix avec number");
        }

        if(n4==0)
        {
             ui->description_2->setStyleSheet("border: 1px solid red");
             ui->label_erreur->setText("remplir le champ description");
        }



    }

}
void gestionfinance::on_supprimer_2_clicked()
{
    int row =ui->tab_finance_2->selectionModel()->currentIndex().row();
    int id=ui->tab_finance_2->model()->index(row,0).data().toInt();
     ui->id_2->setText(QString::number(id));
    int idd =ui->id_2->text().toInt();
    bool test=F.supprimer(idd);
    if(test)
    {
        ui->label_erreur->setText("suppression effectueée\n");

        ui->tab_finance_2->setModel(F.afficher());
    }
    else
        ui->label_erreur->setText("suppression non effectuée\n");

    ui->tab_finance_2->setModel(F.afficher());

}
void gestionfinance::on_pushButton_modifier_2_clicked()
{
int row =ui->tab_finance_2->selectionModel()->currentIndex().row();
int id=ui->tab_finance_2->model()->index(row,0).data().toInt();
QString type=ui->tab_finance_2->model()->index(row,1).data().toString();
QDate date=ui->tab_finance_2->model()->index(row,2).data().toDate();
float prix=ui->tab_finance_2->model()->index(row,3).data().toFloat();
QString description=ui->tab_finance_2->model()->index(row,4).data().toString();
if (row==-1)
{
    ui->label_erreur->setText("aucune sélection\n");

}
else
{
    ui->id_4->setText(QString::number(id));
    ui->type_4->setText(type);
    ui->date_4->setDate(date);
    ui->prix_4->setText(QString::number(prix));
    ui->description_4->setText(description);
}

}

void gestionfinance::on_pushButton_valider_2_clicked()
{
    int id=ui->id_4->text().toInt();
    QString type=ui->type_4->text();
    QString date=ui->date_4->text();
    float prix=ui->prix_4->text().toInt();
    QString description=ui->description_4->text();
    int n= id;
    int n1=type.size();
    int n2=date.size();
    int n3=prix;
    int n4=description.size();
    if((n!=0 and n1!=0 and n2!=0 and n3!=0 and n4!=0))
    {
    ui->label_erreur_2->setText("tous les champs remplir");
    finance F (id,type,date,description,prix);
    bool test =F.modifier_finance();
    if(test)
    {
        ui->label_erreur->setText("modification  effectuée\n");
        ui->tab_finance_2->setModel(F.afficher());
    }
    else
        {
        ui->label_erreur->setText("modification non effectuée\n");

    }
    ui->tab_finance_2->setModel(F.afficher());
}
    else
    {
        if(n==0)
        {
          ui->id_4->setStyleSheet("border: 1px solid red");
          ui->label_erreur_2->setText("remplir le champ id avec number");
        }
        if(n1==0)
        {
           ui->type_4->setStyleSheet("border: 1px solid red");
           ui->label_erreur_2->setText("remplir le champ type");
        }
        if(n2==0)
        {
            ui->date_4->setStyleSheet("border: 1px solid red");
            ui->label_erreur_2->setText("remplir le champ date");
        }
        if(n3==0)
        {
            ui->prix_4->setStyleSheet("border: 1px solid red");
             ui->label_erreur_2->setText("remplir le champ prix avec number");
        }

        if(n4==0)
        {
             ui->description_4->setStyleSheet("border: 1px solid red");
             ui->label_erreur_2->setText("remplir le champ description");
        }



    }
}

void gestionfinance::on_pushButton_ajouterAbonnement_2_clicked()
{
    int code=ui->code_2->text().toInt();
    QString nomC=ui->nomC_2->text();
    QString dateD=ui->dateD_2->text();
    QString dateF=ui->dateF_2->text();
    float prix=ui->prix1_2->text().toFloat();
    int n= code;
    int n1=nomC.size();
    int n2=dateD.size();
    int n3=dateF.size();
    int n4=prix;
    if((n!=0 and n1!=0 and n2!=0 and n3!=0 and n4!=0))
    {
        ui->label_erreur3->setText("tous les champs bien remplis");
    abonnemet A(code,nomC,dateD,dateF,prix);
    bool test =A.ajouter();
    if(test)
    {
        ui->label_erreur3->setText("ajout  effectué\n");

    }
    else
        ui->label_erreur3->setText("ajout non effectué\n");

     ui->table_abonnement_2->setModel(A.afficher());
}
    else
    {
        if(n==0)
        {
          ui->code_2->setStyleSheet("border: 1px solid red");
          ui->label_erreur3->setText("remplir le champ id avec number");
        }
        if(n1==0)
        {
           ui->nomC_2->setStyleSheet("border: 1px solid red");
           ui->label_erreur3->setText("remplir le champ type");
        }
        if(n2==0)
        {
            ui->dateD_2->setStyleSheet("border: 1px solid red");
            ui->label_erreur3->setText("remplir le champ date");
        }
        if(n3==0)
        {
            ui->dateF_2->setStyleSheet("border: 1px solid red");
             ui->label_erreur3->setText("remplir le champ prix avec number");
        }

        if(n4==0)
        {
             ui->prix1_2->setStyleSheet("border: 1px solid red");
             ui->label_erreur3->setText("remplir le champ description");
        }



    }
}
void gestionfinance::on_supprimerAbonnement_2_clicked()
{
int row =ui->table_abonnement_2->selectionModel()->currentIndex().row();
int code=ui->table_abonnement_2->model()->index(row,0).data().toInt();
 ui->code_2->setText(QString::number(code));
int code1 =ui->code_2->text().toInt();
bool test=A.supprimer(code1);
if(test)
{
    ui->label_erreur3->setText("suppression  effectuée\n");

    ui->table_abonnement_2->setModel(F.afficher());
}
else
    ui->label_erreur3->setText("suppression non effectuée\n");

ui->table_abonnement_2->setModel(A.afficher());
}

void gestionfinance::on_rechercher_2_clicked()
{
   QString val =ui->lineEdit_rechercher_2->text();
   int n=val.size();
   if(n!=0)
   {
        ui->lineEdit_rechercher_2->setStyleSheet("border: 3px solid green");
   ui->tab_finance_2->setModel(F.rechercher(val));
   }
   else
   {
       ui->lineEdit_rechercher_2->setStyleSheet("border: 3px solid red");

   }
}

void gestionfinance::on_tri_2_clicked()
{
    ui->tab_finance_2->setModel(F.trieFinanace());
}

void gestionfinance::on_modifierAbonnement_2_clicked()
{
    int row =ui->table_abonnement_2->selectionModel()->currentIndex().row();
    int code=ui->table_abonnement_2->model()->index(row,0).data().toInt();
    QString nomC=ui->table_abonnement_2->model()->index(row,1).data().toString();
    QDate dateD=ui->table_abonnement_2->model()->index(row,2).data().toDate();
    QDate dateF=ui->table_abonnement_2->model()->index(row,3).data().toDate();
    float prix=ui->table_abonnement_2->model()->index(row,4).data().toFloat();
    if (row==-1)
    {
        ui->label_erreur3->setText("aucune selection \n");

    }
    else
    {
        ui->code_2->setText(QString::number(code));
        ui->nomC_2->setText(nomC);
        ui->dateD_2->setDate(dateD);
        ui->dateF_2->setDate(dateF);
        ui->prix1_2->setText(QString::number(prix));
    }

}

void gestionfinance::on_validerModification_2_clicked()
{
    int code=ui->code_2->text().toInt();
    QString nomC=ui->nomC_2->text();
    QString dateD=ui->dateD_2->text();
    QString dateF=ui->dateF_2->text();
    float prix=ui->prix1_2->text().toInt();
    int n= code;
    int n1=nomC.size();
    int n2=dateD.size();
    int n3=dateF.size();
    int n4=prix;
    if((n!=0 and n1!=0 and n2!=0 and n3!=0 and n4!=0))
    {
    ui->label_erreur3->setText("tous les champs bien remplis");
    abonnemet A (code,nomC,dateD,dateF,prix);
    bool test =A.modifier_abonnement();
    if(test)
    {
        ui->label_erreur3->setText("Modification  effectuée\n");
        ui->table_abonnement_2->setModel(A.afficher());
    }
    else
        {
        ui->label_erreur3->setText("Modification non effectuée\n");

    }
    ui->table_abonnement_2->setModel(A.afficher());
    }
    else
    {
        if(n==0)
        {
          ui->code_2->setStyleSheet("border: 1px solid red");
          ui->label_erreur3->setText("remplir le champ id avec number");
        }
        if(n1==0)
        {
           ui->nomC_2->setStyleSheet("border: 1px solid red");
           ui->label_erreur3->setText("remplir le champ type");
        }
        if(n2==0)
        {
            ui->dateD_2->setStyleSheet("border: 1px solid red");
            ui->label_erreur3->setText("remplir le champ date");
        }
        if(n3==0)
        {
            ui->dateF_2->setStyleSheet("border: 1px solid red");
             ui->label_erreur3->setText("remplir le champ prix avec number");
        }

        if(n4==0)
        {
             ui->prix1_2->setStyleSheet("border: 1px solid red");
             ui->label_erreur3->setText("remplir le champ description");
        }



    }

}

void gestionfinance::on_pushButton_pdf_2_clicked()
{
    QString fileName = QFileDialog::getSaveFileName(this, tr("Exportation en fichier Excel"), qApp->applicationDirPath (),
                                                            tr("Fichiers d'extension Excel (*.xls)"));
            if (fileName.isEmpty())
                return;

            ExportExcelObject obj(fileName, "mydata", ui->table_abonnement_2);

            // you can change the column order and
            // choose which colum to export
            obj.addField(0, "code", "char(20)");
            obj.addField(1, "nomClient", "char(20)");
            obj.addField(2, "dateDebut", "char(20)");
            obj.addField(3, "dateFin", "char(20)");
            obj.addField(4, "prix", "char(20)");


            int retVal = obj.export2Excel();

            if( retVal > 0)
            {
                QMessageBox::information(this, tr("FAIS!"),
                                         QString(tr("%1 enregistrements exportés!")).arg(retVal)
                                         );
            }
}

void gestionfinance::on_pushButton_deconnecter_2_clicked()
{
  //  ui->stackedWidget->setCurrentIndex(0);
}

void gestionfinance::on_pushButton_QrCode_clicked()
{
    int tabev=ui->table_abonnement_2->currentIndex().row();
        QVariant idd=ui->table_abonnement_2->model()->data(ui->table_abonnement_2->model()->index(tabev,0));
        QString code= idd.toString();
        QSqlQuery qry;
        qry.prepare("select * from abonnement where code=:code");
        qry.bindValue(":code",code);
        qry.exec();
        QString nomC,dateD,dateF,prix,ids;
        while(qry.next()){
            nomC=qry.value(1).toString();
            dateD=qry.value(2).toString();
            dateF=qry.value(3).toString();
            prix=qry.value(4).toString();

        }
        ids=QString(code);
        ids="ID: "+ids+" Nom: "+nomC+"dateD: "+dateD+"dateF: "+dateF+"prix: "+prix;
        QrCode qr = QrCode::encodeText(ids.toUtf8().constData(), QrCode::Ecc::HIGH);

        // Read the black & white pixels
        QImage im(qr.getSize(),qr.getSize(), QImage::Format_RGB888);
        for (int y = 0; y < qr.getSize(); y++) {
            for (int x = 0; x < qr.getSize(); x++) {
                int color = qr.getModule(x, y);  // 0 for white, 1 for black

                // You need to modify this part
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

void gestionfinance::on_pushButton_save_clicked()
{
    const QString & path = QFileDialog::getSaveFileName( this, QString::null, "qrcode", saveFormats2() );
        if ( path.isNull() )
            return;
        ui->QrCode->pixmap()->save( path );
}

void gestionfinance::on_rechercherAbonnement_4_clicked()
{

}


void gestionfinance::on_pushButton_close_clicked()
{
    close();
}

void gestionfinance::on_pushButton_mail_clicked()
{
    Smtp* smtp;
        const QString mailto="yassinetilouche@gmail.com";

           smtp = new Smtp("tennisclubtunis1@gmail.com", "tennis2021", "smtp.gmail.com");
           //connect(smtp, SIGNAL(clicked()), this, SLOT(on_Mail_clicked()));
           //std::cout<<mailto;

           smtp->sendMail(mailto, mailto , "tennis club","test ");
}


void gestionfinance::on_pushButton_clicked()
{
    hide();
    Rf= new MainWindow(this);
    Rf->show();
}
void gestionfinance::on_google_search_button_clicked()
{
searchEdit.show();
}


void gestionfinance::on_arduino_enter_clicked()
{
    Ar.write_to_arduino("1");

}

void gestionfinance::on_arduino_test_clicked()
{
    Ar.write_to_arduino("2");

}
