#include "dialogmain.h"
#include "ui_dialogmain.h"
#include <QMessageBox>
#include <QPainter>
#include <QtPrintSupport/QPrinter>
#include <QFileDialog>
#include <QTextDocument>
#include "qrcode.h"
#include <QTimer>
#include <QRegularExpression>
#include "exportexcelobjet.h"
#include <QFileDialog>
#include<QTextStream>
using namespace qrcodegen;
Dialogmain::Dialogmain(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialogmain)
{
    ui->setupUi(this);
    ui->tabSeances->setModel(tmpSceance.afficher()); // affichage par defaut des données seances
    ui->tabCours->setModel(tmpCours.afficher()); // affichage par defaut des données cours
    // seance controls
    ui->lineEdit_id_seance->setValidator(new QIntValidator(0,9999999,this)); // controle de saisie id_seance
    // ui->lineEdit_lieu->setValidator(new QRegExpValidator( QRegExp("[A-Za-z ]*") , this )); // controle de saisie lieu seance
    ui->lineEdit_prix->setValidator(new QIntValidator(0,9999999,this)); // controle de saisie prix seance
    ui->id_edit->setDisabled(1);
    ui->id_edit->hide();
    ui->date_edit->hide();
    ui->db_edit->hide();
    ui->fn_edit->hide();
    ui->lieu_edit->hide();
    ui->prix_edit->hide();
    ui->edit_sc->hide();
    ui->delete_sc->hide();
    // cours controls
    ui->cours_id->setValidator(new QIntValidator(0,9999999,this));
    ui->cours_titre->setValidator(new QRegExpValidator( QRegExp("[A-Za-z ]*") , this ));
    ui->cours_nbr_prtc->setValidator(new QIntValidator(0,9999999,this));
    ui->cours_nbr_obj->setValidator(new QIntValidator(0,9999999,this));
    ui->cours_nbr_sc->setValidator(new QIntValidator(0,9999999,this));
    ui->cours_id_edit->setValidator(new QIntValidator(0,9999999,this));
    ui->cours_titre_edit->setValidator(new QRegExpValidator( QRegExp("[A-Za-z ]*") , this ));
    ui->cours_nbr_obj_edit->setValidator(new QIntValidator(0,9999999,this));
    ui->cours_nbr_part_edit->setValidator(new QIntValidator(0,9999999,this));
    ui->cours_nbr_sc_req_edit->setValidator(new QIntValidator(0,9999999,this));
    ui->cours_id_edit->setDisabled(1);
    ui->cours_id_edit->hide();
    ui->cours_titre_edit->hide();
    ui->cours_nbr_obj_edit->hide();
    ui->cours_nbr_part_edit->hide();
    ui->cours_nbr_sc_req_edit->hide();
    ui->edit_cours->hide();
    ui->QR->hide();
    ui->delete_cours->hide();
    // tri controls seance
    ui->id_asc->hide();
    ui->date_asc->hide();
    ui->heuredb_asc->hide();
    ui->heurefn_asc->hide();
    ui->lieu_asc->hide();
    ui->prix_asc->hide();
    // tri controls cours
    ui->npar_desc->hide();
    ui->nobj_desc->hide();
    ui->titre_desc->hide();
    ui->id_desc_2->hide();
    ui->nsea_desc->hide();

}

Dialogmain::~Dialogmain()
{
    delete ui;
}



void Dialogmain::on_nxt_btn_clicked()
{
    ui->stackedWidget_2->setCurrentIndex(1);
}

void Dialogmain::on_prv_btn_clicked()
{
    ui->stackedWidget_2->setCurrentIndex(0);
}

void Dialogmain::on_nxt_md_btn_clicked()
{
     ui->stackedWidget->setCurrentIndex(1);
}

void Dialogmain::on_prv_md_btn_clicked()
{
    ui->stackedWidget->setCurrentIndex(0);
}

void Dialogmain::on_add_sc_btn_clicked()
{
   int id_seance =ui->lineEdit_id_seance->text().toInt();
   QString date_seance =ui->dateEdit_seance->date().toString("yyyy/MM/dd");
   QString heure_debut=ui->debut_seance->time().toString("h:mm ap");
   QString heure_fin = ui->fin_seance->time().toString("h:mm ap");
   QString lieu = ui->lineEdit_lieu->currentText();
   int prix_seance = ui->lineEdit_prix->text().toInt();
   if (id_seance != 0) {
   seances s(id_seance,date_seance,heure_debut,heure_fin,lieu,prix_seance);
   bool test=s.ajouter();
   if (test){
       ui->tabSeances->setModel(tmpSceance.afficher());

       QMessageBox::information (nullptr, QObject::tr("ADD"),
                   QObject::tr("\n ADDED SUCCESSFULY !\n"), QMessageBox::Cancel);

       ui->lineEdit_id_seance->clear();
       ui->dateEdit_seance->clear();
       ui->debut_seance->clear();
       ui->fin_seance->clear();

       ui->lineEdit_prix->clear();

   }
   else
           QMessageBox::critical(nullptr, QObject::tr("ADD"),
                       QObject::tr("\n ERROR ID IS PK  !\n"), QMessageBox::Cancel);

   ui->lineEdit_id_seance->clear();
   ui->dateEdit_seance->clear();
   ui->debut_seance->clear();
   ui->fin_seance->clear();

   ui->lineEdit_prix->clear(); }
   else
       QMessageBox::critical(nullptr, QObject::tr("ADD"),
                              QObject::tr("\n ID CAN NOT BE NULL !\n"), QMessageBox::Cancel);





}

void Dialogmain::on_tabSeances_activated(const QModelIndex &index)
{
    QString val=ui->tabSeances->model()->data(index).toString();
        QSqlQuery qry;
        qry.prepare("Select * from seances where id_seance='"+val+"'");
        if(qry.exec())
        {
            while(qry.next())
                    {
                        ui->id_edit->setText(qry.value(0).toString());
                        ui->date_edit->setText(qry.value(1).toString());
                        ui->db_edit->setText(qry.value(2).toString());
                        ui->fn_edit->setText(qry.value(3).toString());
                        //ui->lieu_edit->itemText(qry.value(4).toString());
                        ui->prix_edit->setText(qry.value(5).toString());

                        ui->id_edit ->show();

                        ui-> date_edit->show();
                        ui->db_edit ->show();
                        ui->fn_edit->show();
                        ui->lieu_edit ->show();
                        ui->prix_edit->show();
                        ui->edit_sc ->show();
                        ui->delete_sc ->show();


                    }
        }
}

void Dialogmain::on_edit_sc_clicked()
{
    int id_seance=ui->id_edit->text().toInt();
    QString date_seance=ui->date_edit->text();
    QString heure_debut=ui->db_edit->text();
    QString heure_fin=ui -> fn_edit->text();
    QString lieu=ui-> lieu_edit->currentText();
    int prix_seance=ui->prix_edit->text().toInt();

    seances e(id_seance,date_seance,heure_debut,heure_fin,lieu,prix_seance);
    bool test=e.modifier(id_seance) ;
    if (test) {
         ui->tabSeances->setModel(tmpSceance.afficher());
         QMessageBox::information(nullptr, QObject::tr("MODIFY"),
                                       QObject::tr("MODIFIED SUCCESSFULY ! ! .\n"
                                                   "Click Ok to exit."), QMessageBox::Ok);
         ui->id_edit->hide();
         ui->date_edit->hide();
         ui->db_edit->hide();
         ui->fn_edit->hide();
         ui->lieu_edit->hide();
         ui->prix_edit->hide();
         ui->edit_sc->hide();
         ui->delete_sc->hide();
    }
    else {
        QMessageBox::critical(nullptr, QObject::tr("MODIFY"),
                           QObject::tr("ERROR FILL ALL THE INFO.\n"
                                       "Click Cancel to exit."), QMessageBox::Cancel);
    }


}

void Dialogmain::on_delete_sc_clicked()
{
int id = ui->id_edit->text().toInt();
bool test=tmpSceance.supprimer(id);
if (test){
    ui->tabSeances->setModel(tmpSceance.afficher());
    ui->id_edit->hide();
    ui->date_edit->hide();
    ui->db_edit->hide();
    ui->fn_edit->hide();
    ui->lieu_edit->hide();
    ui->prix_edit->hide();
    ui->edit_sc->hide();
    ui->delete_sc->hide();
}
}


void Dialogmain::on_add_cr_btn_clicked()
{
    int id_cours = ui->cours_id ->text().toInt();
    QString titre = ui->cours_titre->text();
    int nbr_obj = ui->cours_nbr_obj ->text().toInt();
    int nbr_prtc = ui->cours_nbr_prtc ->text().toInt();
    int nbr_sc = ui->cours_nbr_sc ->text().toInt();
    if (id_cours!=0) {
    cours s(id_cours,titre,nbr_obj,nbr_prtc,nbr_sc);
    bool test=s.ajouter();
    if (test){
        ui->tabCours->setModel(tmpCours.afficher());

        QMessageBox::information (nullptr, QObject::tr("ADD"),
                    QObject::tr("\n ADDED SUCCESSFULY !\n"), QMessageBox::Cancel);

        ui->cours_id->clear();
        ui->cours_titre->clear();
        ui->cours_nbr_obj->clear();
        ui->cours_nbr_prtc->clear();
        ui->cours_nbr_sc->clear();


    }
    else
            QMessageBox::critical(nullptr, QObject::tr("ADD"),
                        QObject::tr("\n ERROR ID IS A PK !\n"), QMessageBox::Cancel);

    ui->lineEdit_id_seance->clear();
    ui->dateEdit_seance->clear();
    ui->debut_seance->clear();
    ui->fin_seance->clear();
    ui->lineEdit_lieu->clear();
    ui->lineEdit_prix->clear();
     }
    else
            QMessageBox::critical(nullptr, QObject::tr("ADD"),
                        QObject::tr("\n ID CAN NOT BE NULL !\n"), QMessageBox::Cancel);

}

void Dialogmain::on_tabCours_activated(const QModelIndex &index)
{
    QString val=ui->tabCours->model()->data(index).toString();
        QSqlQuery qry;
        qry.prepare("Select * from cours where id_cours='"+val+"'");
        if(qry.exec())
        {
            while(qry.next())
                    {
                        ui->cours_id_edit->setText(qry.value(0).toString());
                        ui->cours_titre_edit->setText(qry.value(1).toString());
                        ui->cours_nbr_obj_edit->setText(qry.value(2).toString());
                        ui->cours_nbr_part_edit->setText(qry.value(3).toString());
                        ui->cours_nbr_sc_req_edit->setText(qry.value(4).toString());


                        ui->cours_id_edit ->show();
                        ui->cours_titre_edit->show();
                        ui->cours_nbr_obj_edit ->show();
                        ui->cours_nbr_part_edit->show();
                        ui->cours_nbr_sc_req_edit ->show();
                        ui->edit_cours->show();
                        ui->QR->show();
                        ui->delete_cours ->show();



                    }
        }
}

void Dialogmain::on_edit_cours_clicked()
{
    int cours_id=ui->cours_id_edit->text().toInt();
    QString titre =ui->cours_titre_edit->text();
    int nbr_obj=ui->cours_nbr_obj_edit->text().toInt();
    int nbr_part=ui -> cours_nbr_part_edit->text().toInt();
    int nbr_sc=ui-> cours_nbr_sc_req_edit->text().toInt();


    cours  e(cours_id,titre,nbr_obj,nbr_part,nbr_sc);
    bool test=e.modifier(cours_id) ;
    if (test) {
         ui->tabCours->setModel(tmpCours.afficher());
         QMessageBox::information(nullptr, QObject::tr("MODIFY"),
                                       QObject::tr("MODIFIED SUCCESSFULY ! ! .\n"
                                                   "Click Ok to exit."), QMessageBox::Ok);
         ui->cours_id_edit->hide();
         ui->cours_titre_edit->hide();
         ui->cours_nbr_obj_edit->hide();
         ui->cours_nbr_part_edit->hide();
         ui->cours_nbr_sc_req_edit->hide();
         ui->edit_cours->hide();
         ui->delete_cours->hide();

    }
    else {
        QMessageBox::critical(nullptr, QObject::tr("MODIFY"),
                           QObject::tr("ERROR FILL ALL THE INFO.\n"
                                       "Click Cancel to exit."), QMessageBox::Cancel);
    }
}

void Dialogmain::on_delete_cours_clicked()
{
    int id = ui->cours_id_edit->text().toInt();
    bool test=tmpCours.supprimer(id);
    if (test){
        ui->tabCours->setModel(tmpCours.afficher());
        ui->cours_id_edit->hide();
        ui->cours_titre_edit->hide();
        ui->cours_nbr_obj_edit->hide();
        ui->cours_nbr_part_edit->hide();
        ui->cours_nbr_sc_req_edit->hide();
        ui->edit_cours->hide();
        ui->delete_cours->hide();
    }
}

void Dialogmain::on_id_asc_clicked()
{
    ui->id_asc->hide();
    ui->tabSeances->setModel(tmpSceance.affichertri(0));
    ui->id_desc->show();

}

void Dialogmain::on_id_desc_clicked()
{
    ui->id_asc->show();
    ui->tabSeances->setModel(tmpSceance.affichertri(1));
    ui->id_desc->hide();
}

void Dialogmain::on_date_asc_clicked()
{
    ui->date_asc->hide();
    ui->tabSeances->setModel(tmpSceance.affichertri(2));
    ui->date_desc->show();
}
void Dialogmain::on_date_desc_clicked()
{
    ui->date_asc->show();
    ui->tabSeances->setModel(tmpSceance.affichertri(3));
    ui->date_desc->hide();
}



void Dialogmain::on_heuredb_asc_clicked()
{
    ui->heuredb_asc->hide();
    ui->tabSeances->setModel(tmpSceance.affichertri(4));
    ui->heuredb_desc->show();
}
void Dialogmain::on_heuredb_desc_clicked()
{
    ui->heuredb_asc->show();
    ui->tabSeances->setModel(tmpSceance.affichertri(5));
    ui->heuredb_desc->hide();
}


void Dialogmain::on_heurefn_asc_clicked()
{
    ui->heurefn_asc->hide();
    ui->tabSeances->setModel(tmpSceance.affichertri(6));
    ui->heurefn_desc->show();
}

void Dialogmain::on_heurefn_desc_clicked()
{
    ui->heurefn_asc->show();
    ui->tabSeances->setModel(tmpSceance.affichertri(7));
    ui->heurefn_desc->hide();
}

void Dialogmain::on_lieu_asc_clicked()
{
    ui->lieu_asc->hide();
    ui->tabSeances->setModel(tmpSceance.affichertri(8));
    ui->lieu_desc->show();
}


void Dialogmain::on_lieu_desc_clicked()
{
    ui->lieu_asc->show();
    ui->tabSeances->setModel(tmpSceance.affichertri(9));
    ui->lieu_desc->hide();
}

void Dialogmain::on_prix_asc_clicked()
{
    ui->prix_desc->show();
    ui->tabSeances->setModel(tmpSceance.affichertri(10));
    ui->prix_asc->hide();
}

void Dialogmain::on_prix_desc_clicked()
{
    ui->prix_asc->show();
    ui->tabSeances->setModel(tmpSceance.affichertri(11));
    ui->prix_desc->hide();
}

void Dialogmain::on_search_textChanged(const QString &arg1)
{

    QSqlQueryModel *model= new QSqlQueryModel();
    QSqlQuery   *query= new QSqlQuery();
    query->prepare("SELECT * FROM seanceS WHERE id_seance LIKE'"+arg1+"%' or date_seance LIKE'"+arg1+"%' or heure_debut LIKE'"+arg1+"%' or heure_fin like'"+arg1+"%' or lieu like '"+arg1+"%'  or prix_seance like '"+arg1+"%'");
     query->exec();
    if(query->next())
    {
     model->setQuery(*query);
     ui->tabSeances->setModel(model);
    }
    else
    {
        QMessageBox::critical(nullptr, QObject::tr("SEANCE"),
                        QObject::tr("NO MATCH FOUND !.\n"
                                    "Click Cancel to exit."), QMessageBox::Cancel);
        ui->search->clear();

    }
}
// cours search
void Dialogmain::on_lineEdit_textChanged(const QString &arg1)
{
    QSqlQueryModel *model= new QSqlQueryModel();
    QSqlQuery   *query= new QSqlQuery();
    query->prepare("SELECT * FROM cours WHERE id_cours LIKE'"+arg1+"%' or titre LIKE'"+arg1+"%' or nombre_objectif LIKE'"+arg1+"%' or nombre_participants like'"+arg1+"%' or nombre_de_seances_requises like '"+arg1+"%'");
     query->exec();
    if(query->next())
    {
     model->setQuery(*query);
     ui->tabCours->setModel(model);
    }
    else
    {
        QMessageBox::critical(nullptr, QObject::tr("COURS"),
                        QObject::tr("NO MATCH FOUND !.\n"
                                    "Click Cancel to exit."), QMessageBox::Cancel);
        ui->lineEdit->clear();

    }
}

void Dialogmain::on_pushButton_clicked()
{
    statistiques d;
    d.exec();
}

void Dialogmain::on_id_asc_2_clicked()
{
    ui->id_asc_2->hide();
    ui->tabCours->setModel(tmpCours.affichertri(0));
    ui->id_desc_2->show();
}

void Dialogmain::on_id_desc_2_clicked()
{
    ui->id_asc_2->show();
    ui->tabCours->setModel(tmpCours.affichertri(1));
    ui->id_desc_2->hide();
}

void Dialogmain::on_titre_asc_clicked()
{
    ui->titre_desc->show();
    ui->tabCours->setModel(tmpCours.affichertri(2));
    ui->titre_asc->hide();
}

void Dialogmain::on_titre_desc_clicked()
{
    ui->titre_asc->show();
    ui->tabCours->setModel(tmpCours.affichertri(3));
    ui->titre_desc->hide();
}

void Dialogmain::on_nobj_asc_clicked()
{
    ui->nobj_desc->show();
    ui->tabCours->setModel(tmpCours.affichertri(4));
    ui->nobj_asc->hide();
}

void Dialogmain::on_nobj_desc_clicked()
{
    ui->nobj_asc->show();
    ui->tabCours->setModel(tmpCours.affichertri(5));
    ui->nobj_desc->hide();
}

void Dialogmain::on_npar_asc_clicked()
{
    ui->npar_desc->show();
    ui->tabCours->setModel(tmpCours.affichertri(6));
    ui->npar_asc->hide();
}

void Dialogmain::on_npar_desc_clicked()
{
    ui->npar_asc->show();
    ui->tabCours->setModel(tmpCours.affichertri(7));
    ui->npar_desc->hide();
}

void Dialogmain::on_nsea_asc_clicked()
{
    ui->nsea_desc->show();
    ui->tabCours->setModel(tmpCours.affichertri(8));
    ui->nsea_asc->hide();
}

void Dialogmain::on_nsea_desc_clicked()
{
    ui->nsea_asc->show();
    ui->tabCours->setModel(tmpCours.affichertri(9));
    ui->nsea_desc->hide();
}

void Dialogmain::on_dark_btn_clicked(){

}
void Dialogmain::on_pushButton_2_clicked()
{
    QString fileName = QFileDialog::getSaveFileName(this, tr("Exportation en fichier Excel"), qApp->applicationDirPath (),
                                                            tr("Fichiers d'extension Excel (*.xls)"));
            if (fileName.isEmpty())
                return;

            ExportExcelObject obj(fileName, "mydata", ui->tabSeances);

            // you can change the column order and
            // choose which colum to export
            obj.addField(0, "Id_Seance", "char(20)");
            obj.addField(1, "Date", "char(20)");
            obj.addField(2, "heure_debut", "char(20)");
            obj.addField(3, "heure_fin", "char(20)");
           obj.addField(4, "lieu", "char(20)");
            obj.addField(5, "prix", "char(20)");


            int retVal = obj.export2Excel();

            if( retVal > 0)
            {
                QMessageBox::information(this, tr("FAIS!"),
                                         QString(tr("%1 enregistrements exportés!")).arg(retVal)
                                         );
            }
}

void Dialogmain::on_checkBox_stateChanged(int arg1)
{
    if (arg1==2)

    {
        QFile styleSheetFile("C:\\Users\\hp\\Desktop\\SID\\SMART CLUB\\dark.qss");
            styleSheetFile.open(QFile::ReadOnly);
            QString styleSheet = QLatin1String(styleSheetFile.readAll());
            this->setStyleSheet(styleSheet);
    }
    else
    {
        this->setStyleSheet("");
    }
}


void Dialogmain::on_QR_clicked()
{
            int id = ui->cours_id_edit->text().toInt();
            QString ids;
            ids="ID: "+id;
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
            im=im.scaled(200,200);
            ui->QR_label->setPixmap(QPixmap::fromImage(im));

}

void Dialogmain::on_retour_seance_clicked()
{
  hide();
  Rs = new MainWindow(this);
  Rs->show();
}
void Dialogmain::on_google_search_button_clicked()
{
searchEdit.show();
}
