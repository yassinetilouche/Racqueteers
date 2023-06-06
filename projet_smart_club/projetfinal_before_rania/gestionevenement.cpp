#include "gestionevenement.h"
#include "ui_gestionevenement.h"
#include "evenement.h"
#include "sponsors.h"
#include <QMessageBox>
#include <QApplication>
#include <QSqlQuery>
#include <iostream>
#include <QDebug>
#include <QDateTime>
#include<QCompleter>
#include <QVector>
#include <algorithm>
#include "exportexcelobjet.h"
#include "stmp.h"

gestionevenement::gestionevenement(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::gestionevenement)
{
    QCompleter *completerEven = new QCompleter();
    ui->setupUi(this);
    QPixmap pix("C:/Users/Yassine/Downloads/tennislogo.png");
    int w =ui->logo->width();
    int h=ui->logo->height();
    ui->logo->setPixmap(pix.scaled(w,h,Qt::KeepAspectRatio));
    timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(real_Time_status()));
    timer->start(1000);
    completerEven->setModel(e.rechercherEvenement());
    ui->tab_evenement->setModel(e.afficher());
    ui->ligne->setEnabled(false);
    //ui->ligne->setText(ui->tab_evenement->row);
    n = e.number();
    //qDebug()<<"LINE:"<<n;
    ui->ligne->setText(QString::number(n));
    ui->tab_sponsors->setModel(sp.afficher());
    //ui->evenementT->setModel(e.afficher());
    //ui->sponsorsT->setModel(sp.afficher());
    //ui->ligne->setText();
    ui->le_id->setValidator(new QIntValidator(0,9999999,this));
    ui->le_idS->setValidator(new QIntValidator(0,9999999,this));
    ui->le_tel->setValidator(new QIntValidator(0,9999999,this));

    ui->id_edit->hide();
    ui->type_edit->hide();
    ui->date_edit->hide();
    ui->time_edit->hide();
    ui->place_edit->hide();
    ui->lieu_edit->hide();

    ui->pb_mod->hide();
    ui->pb_supp->hide();

    ui->ids_edit->hide();
    ui->tel_edit->hide();
    ui->nom_edit->hide();
    ui->email_edit->hide();
    ui->typeS_edit->hide();
    ui->mat_edit->hide();

    ui->modifierS->hide();
    ui->supprimerS->hide();
    ui->acces->hide();
    ui->refuse->hide();

    ui->pb_mail->hide();

    ui->le_search->setCompleter(completerEven);
    stats();

    int rect = A.connect_arduino();
    //qDebug()<<"test";
    switch(rect)
    {
        case(0):
        qDebug() <<"Arduino is available  and connected to :"<<A.getarduino_port_name();
        break;
    case(1):
        qDebug() <<"Arduino is available  but not connected to :"<< A.getarduino_port_name();
        break;
    case(-1):
        qDebug() <<"Arduino is not available ";
        break;
    }

    if(rect != -1)
    QObject::connect(A.getserial(),SIGNAL(readyRead()), this, SLOT(update_label()));

}

gestionevenement::~gestionevenement()
{
    delete ui;
}

QString gestionevenement::Fetch_Month(int m)
{
    QString month;
    switch(m)
    {
        case 1:
        month = "janvier";
        break;

    case 2:
        month = "Fevrier";
        break;

    case 3:
        month = "Mars";
        break;

    case 4:
        month = "Avril";
        break;

    case 5:
        month = "Mai";
        break;
    case 6:
        month = "Juin";
        break;

    case 7:
        month = "Juillet";
        break;

    case 8:
        month = "Aout";
        break;

    case 9:
        month = "September";
        break;

    case 10:
        month = "October";
        break;

    case 11:
        month = "Novembre";
        break;

    case 12:
        month = "Decemebre";
        break;


    }

    return month;
}

void gestionevenement::update_graph()
{
    qDebug() <<ui->customPlot->graphCount();

    ui->customPlot->removeGraph(0);

    ui->customPlot->replot();
    stats();
}

/*void gestionevenement::french()
{
    ui->
}*/


void gestionevenement::on_pb_ajouter_clicked()
{


    int id = ui->le_id->text().toInt();
    QString type = ui->le_type->text();
    QString date = ui->le_date->date().toString("dd/MM/yy");
    QString heure = ui->le_heure->time().toString("hh:mm ap");
    int place = ui->le_place->text().toInt();
    QString lieu = ui->le_lieu->text();
    Evenement E(id,type,date,heure,place,lieu);

    if(!E.getType().isEmpty() && !E.getDate().isEmpty() && !E.getHeure().isEmpty() && !E.getLieu().isEmpty()){
        bool test = E.ajouter();

        if(test)
        {
            ui->tab_evenement->setModel(e.afficher());
            QMessageBox::information(nullptr, QObject::tr("OK"), QObject::tr("Ajout effectue\n" "Click to exit."), QMessageBox::Cancel);
            update_graph();

            ui->le_id->clear();
            ui->le_type->clear();
            ui->le_date->clear();
            ui->le_heure->clear();
            ui->le_place->clear();
            ui->le_lieu->clear();
        }
        else
        {
            QMessageBox::critical(nullptr, QObject::tr("Not ok"), QObject::tr("Ajout non effectue.\n" "Click cancel to exit."), QMessageBox::Cancel);
        }
     }
    else
    {
        QMessageBox::critical(nullptr, QObject::tr("Error"), QObject::tr("Fill empty blanks"), QMessageBox::Cancel);
    }
}

void gestionevenement::on_pb_reset_clicked()
{
    ui->le_id->clear();
    ui->le_type->clear();
    ui->le_date->clear();
    ui->le_heure->clear();
    ui->le_place->clear();
    ui->le_lieu->clear();
}

void gestionevenement::on_tab_evenement_activated(const QModelIndex &index)
{
    std::cout<<"Worked";
    QString val = ui->tab_evenement->model()->data(index).toString();
    QSqlQuery qry;
    qry.prepare("select * from evenements where ID = " + val );
    if(qry.exec())
    {
        while(qry.next())
        {
            ui->id_edit->setText(qry.value(0).toString());
            ui->type_edit->setText(qry.value(1).toString());
            //std::cout<<qry.value(2);
            ui->date_edit->setDate(qry.value(2).toDate());
            ui->time_edit->setTime(qry.value(3).toTime());
            ui->place_edit->setValue(qry.value(4).toInt());
            ui->lieu_edit->setText(qry.value(5).toString());

            ui->id_edit->show();
            ui->type_edit->show();
            ui->date_edit->show();
            ui->time_edit->show();
            ui->place_edit->show();
            ui->lieu_edit->show();
            ui->pb_mod->show();
            ui->pb_supp->show();
        }

    }
}

void gestionevenement::on_pb_supp_clicked()
{
    int id = ui->id_edit->text().toInt();
    bool test = e.supprimer(id);

    if(test)
    {
        QMessageBox::information(nullptr,QObject::tr("Done"),QObject::tr("Suppression effectué"),QMessageBox::Ok);
        ui->tab_evenement->setModel(e.afficher());
        update_graph();
        ui->id_edit->hide();
        ui->type_edit->hide();
        ui->date_edit->hide();
        ui->time_edit->hide();
        ui->place_edit->hide();
        ui->lieu_edit->hide();
        ui->pb_mod->hide();
        ui->pb_supp->hide();
    }
}

void gestionevenement::on_pb_search_clicked()
{
    //std::cout<<"worked";
    QString s = ui->le_search->text();
    if(s.isEmpty()){
        QMessageBox::critical(nullptr,QObject::tr("erreur"),QObject::tr("Veuillez remplir les champs vides"),QMessageBox::Cancel);
    }
    else
    //std::cout<<s.toLocal8Bit().constData();
    ui->tab_evenement->setModel(e.rechercher(s));
}

void gestionevenement::on_pb_annuler_clicked()
{
    ui->tab_evenement->setModel(e.afficher());
}

void gestionevenement::on_pb_mod_clicked()
{
    int id = ui->id_edit->text().toInt();
    QString type = ui->type_edit->text();
    QString date = ui->date_edit->date().toString("dd/MM/yy");
    QString heure = ui->time_edit->time().toString("hh:mm ap");
    int place = ui->place_edit->text().toInt();
    QString lieu = ui->lieu_edit->text();
    Evenement E(id,type,date,heure,place,lieu);

    bool test = E.modifier(id);

    if(test)
    {
        ui->tab_evenement->setModel(e.afficher());
        QMessageBox::information(nullptr, QObject::tr("OK"), QObject::tr("Modification effectue\n" "Click to exit."), QMessageBox::Cancel);

        update_graph();
        ui->id_edit->hide();
        ui->type_edit->hide();
        ui->date_edit->hide();
        ui->time_edit->hide();
        ui->place_edit->hide();
        ui->lieu_edit->hide();
        ui->pb_mod->hide();
        ui->pb_supp->hide();
    }
    else
    {
        QMessageBox::critical(nullptr, QObject::tr("Not ok"), QObject::tr("Modification non effectue.\n" "Click cancel to exit."), QMessageBox::Cancel);
    }
}



void gestionevenement::on_pb_c_clicked()
{
    ui->tab_evenement->setModel(e.triAsc());
}

void gestionevenement::on_pb_a_clicked()
{
    ui->tab_evenement->setModel(e.triDesc());
}

void gestionevenement::on_pb_print_clicked()
{
    e.pdf("C:\\Users\\Ramez\\Desktop\\qt\\projet\\printer\\hello");
}

void gestionevenement::on_pb_ajouterS_clicked()
{
    int id1 = ui->le_idS->text().toInt();
    int tel1 = ui->le_tel->text().toInt();
    QString nom1 = ui->le_nom->text();
    QString email1 = ui->le_email->text();
    QString type1 = ui->le_typeS->text();
    QString mat1 = ui->le_mat->text();

    Sponsors sp1(id1, tel1, nom1, email1, type1, mat1);

    if(!sp1.getType().isEmpty() && !sp1.getEmail().isEmpty() && !sp1.getMateriels().isEmpty()){
        if(sp1.getEmail().indexOf("@") == -1 && sp1.getEmail().indexOf(".") == -1){
            QMessageBox::critical(nullptr, QObject::tr("Error"), QObject::tr("Email non valide"), QMessageBox::Cancel);

        }
        else
        {
                bool test = sp1.ajouter();

                if(test)
                {
                    ui->tab_sponsors->setModel(sp.afficher());
                    QMessageBox::information(nullptr, QObject::tr("OK"), QObject::tr("Ajout effectue\n" "Click to exit."), QMessageBox::Cancel);
                }
                else
                {
                    QMessageBox::critical(nullptr, QObject::tr("Not ok"), QObject::tr("Ajout non effectue.\n" "Click cancel to exit."), QMessageBox::Cancel);
                }
          }

    }
    else
    {
        QMessageBox::critical(nullptr, QObject::tr("Error"), QObject::tr("Fill empty blanks"), QMessageBox::Cancel);
    }
}

void gestionevenement::on_tab_sponsors_activated(const QModelIndex &index)
{
    QString val = ui->tab_sponsors->model()->data(index).toString();
    QSqlQuery qry;
    qry.prepare("select * from sponsors where ID = " + val );

    if(qry.exec())
    {
        while(qry.next())
        {
            ui->ids_edit->setText(qry.value(0).toString());
            ui->tel_edit->setText(qry.value(1).toString());
            //std::cout<<qry.value(2);
            ui->nom_edit->setText(qry.value(2).toString());
            ui->email_edit->setText(qry.value(3).toString());
            ui->typeS_edit->setText(qry.value(4).toString());
            ui->mat_edit->setText(qry.value(5).toString());

            ui->ids_edit->show();
            ui->tel_edit->show();
            ui->nom_edit->show();
            ui->email_edit->show();
            ui->typeS_edit->show();
            ui->mat_edit->show();
            ui->modifierS->show();
            ui->supprimerS->show();
            ui->pb_mail->show();
        }

    }
}

void gestionevenement::on_supprimerS_clicked()
{
    int id1 = ui->ids_edit->text().toInt();
    bool test = sp.supprimer(id1);

    if(test)
    {
        QMessageBox::information(nullptr,QObject::tr("Done"),QObject::tr("Suppression effectué"),QMessageBox::Ok);
        ui->tab_sponsors->setModel(sp.afficher());
        ui->ids_edit->hide();
        ui->tel_edit->hide();
        ui->nom_edit->hide();
        ui->email_edit->hide();
        ui->typeS_edit->hide();
        ui->mat_edit->hide();

        ui->modifierS->hide();
        ui->supprimerS->hide();
    }

}

void gestionevenement::on_modifierS_clicked()
{
    int id1 = ui->ids_edit->text().toInt();
    int tel1 = ui->tel_edit->text().toInt();
    QString nom1 = ui->nom_edit->text();
    QString email1 = ui->email_edit->text();
    QString type1 = ui->typeS_edit->text();
    QString mat1 = ui->mat_edit->text();
    Sponsors p(id1, tel1, nom1, email1, type1, mat1);

    bool test = p.modifier(id1);

    if(test)
    {
        QMessageBox::information(nullptr,QObject::tr("Done"),QObject::tr("Modification effectué"),QMessageBox::Ok);
        ui->tab_sponsors->setModel(sp.afficher());
        ui->ids_edit->hide();
        ui->tel_edit->hide();
        ui->nom_edit->hide();
        ui->email_edit->hide();
        ui->typeS_edit->hide();
        ui->mat_edit->hide();

        ui->modifierS->hide();
        ui->supprimerS->hide();
        ui->pb_mail->hide();
    }
}

void gestionevenement::on_searchS_pb_clicked()
{
    QString s = ui->searchS->text();
    if(s.isEmpty()){
        QMessageBox::critical(nullptr,QObject::tr("erreur"),QObject::tr("Veuillez remplir les champs vides"),QMessageBox::Cancel);
    }
    else
    //std::cout<<s.toLocal8Bit().constData();
    ui->tab_sponsors->setModel(sp.rechercher(s));
}

void gestionevenement::on_annulerS_pb_clicked()
{
    ui->tab_sponsors->setModel(sp.afficher());
}

void gestionevenement::on_up_clicked()
{
    ui->tab_sponsors->setModel(sp.triAsc());
}

void gestionevenement::on_down_clicked()
{
    ui->tab_sponsors->setModel(sp.triDesc());
}

void gestionevenement::update_label()
{
    data  = A.read_from_arduino();

    if( data == "")
    {
        ui->acces->show();
        ui->id_scanne->setText(data);
    }

    else {
        ui->refuse->hide();
    }
}

void gestionevenement::on_pb_mail_clicked()
{
    Smtp* smtp;
    const QString mailto= ui->email_edit->text();
    //QString contenu;

    smtp = new Smtp("tennisclubtunis1@gmail.com", "tennis2021", "smtp.gmail.com");
            //connect(smtp, SIGNAL(clicked()), this, SLOT(on_Mail_clicked()));
            //std::cout<<mailto;
    QString nom = ui->nom_edit->text();
    QString tel = ui->tel_edit->text();
    QString mat = ui->mat_edit->text();
    QString type = ui->typeS_edit->text();
    //contenu = "Le sponsor " + nom + "a ete enregistre :\n" + "Telephone : " + tel + "\n" + "Materiels fourni : " + mat + "\n" + "Type :" + type + "\nCordialement";
    //qDebug() <<"Hello"<<contenu;
    smtp->sendMail(mailto, mailto , "tennis club","Le sponsor " + nom + " a ete enregistre" );
}

void gestionevenement::real_Time_status()
{
    QTime time = QTime::currentTime();
    QString time_text = time.toString("hh : mm : ss");
    ui->timer->setText(time_text);
    ui->timerS->setText(time_text);
}

void gestionevenement::stats()
{
    int m = QDate::currentDate().month(), y = QDate::currentDate().year();


    QVector<double> data = e.data_from_Base(m, y);

    QLinearGradient gradient(0, 0, 0, 400);
    gradient.setColorAt(0, QColor(90, 90, 90));
    gradient.setColorAt(0.38, QColor(105, 105, 105));
    gradient.setColorAt(1, QColor(70, 70, 70));
    ui->customPlot->setBackground(QBrush(gradient));

    QCPBars *Bar_Date = new QCPBars(ui->customPlot->xAxis, ui->customPlot->yAxis);
    Bar_Date->setAntialiased(false);
    Bar_Date->setStackingGap(1);

    Bar_Date->setName(QString::number(y));
    Bar_Date->setPen(QPen(QColor(111, 9, 176).lighter(170)));
    Bar_Date->setBrush(QColor(111, 9, 176));

    //stack bars

    //prepare x
    QVector<double> ticks;
    QVector<QString> labels;
    ticks << 1 << 2 << 3 ;
    labels << Fetch_Month(m) << Fetch_Month(m + 1) << Fetch_Month(m + 2);
    QSharedPointer<QCPAxisTickerText> textTicker(new QCPAxisTickerText);
    textTicker->addTicks(ticks, labels);
    ui->customPlot->xAxis->setTicker(textTicker);
    ui->customPlot->xAxis->setTickLabelRotation(60);
    ui->customPlot->xAxis->setSubTicks(false);
    ui->customPlot->xAxis->setTickLength(0, 4);
    ui->customPlot->xAxis->setRange(0, 8);
    ui->customPlot->xAxis->setBasePen(QPen(Qt::white));
    ui->customPlot->xAxis->setTickPen(QPen(Qt::white));
    ui->customPlot->xAxis->grid()->setVisible(true);
    ui->customPlot->xAxis->grid()->setPen(QPen(QColor(130, 130, 130), 0, Qt::DotLine));
    ui->customPlot->xAxis->setTickLabelColor(Qt::white);
    ui->customPlot->xAxis->setLabelColor(Qt::white);

    //prepare y
    ui->customPlot->yAxis->setRange(0, *(std::max_element(data.begin(), data.end())));
    ui->customPlot->yAxis->setPadding(5); // a bit more space to the left border
    ui->customPlot->yAxis->setLabel("Nombre des Evenements par mois");
    ui->customPlot->yAxis->setBasePen(QPen(Qt::white));
    ui->customPlot->yAxis->setTickPen(QPen(Qt::white));
    ui->customPlot->yAxis->setSubTickPen(QPen(Qt::white));
    ui->customPlot->yAxis->grid()->setSubGridVisible(true);
    ui->customPlot->yAxis->setTickLabelColor(Qt::white);
    ui->customPlot->yAxis->setLabelColor(Qt::white);
    ui->customPlot->yAxis->grid()->setPen(QPen(QColor(130, 130, 130), 0, Qt::SolidLine));
    ui->customPlot->yAxis->grid()->setSubGridPen(QPen(QColor(130, 130, 130), 0, Qt::DotLine));

    //set Data
    //QVector<double> doubleData(data.begin(), data.end());
    Bar_Date->setData(ticks, data);

    //setup legend
    ui->customPlot->legend->setVisible(true);
    ui->customPlot->axisRect()->insetLayout()->setInsetAlignment(0, Qt::AlignTop|Qt::AlignHCenter);
    ui->customPlot->legend->setBrush(QColor(255, 255, 255, 100));
    ui->customPlot->legend->setBorderPen(Qt::NoPen);
    QFont legendFont = font();
    legendFont.setPointSize(10);
    ui->customPlot->legend->setFont(legendFont);
    ui->customPlot->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom);

    //ui->customPlot->graph()->data()->clear();
    //ui->customPlot->replot();
}

void gestionevenement::on_excel_clicked()
{
    QString fileName = QFileDialog::getSaveFileName(this, tr("Exportation en fichier Excel"), qApp->applicationDirPath (),
                                                                tr("Fichiers d'extension Excel (*.xls)"));
                if (fileName.isEmpty())
                    return;

                ExportExcelObject obj(fileName, "mydata", ui->tab_evenement);

                // you can change the column order and
                // choose which colum to export
                obj.addField(0, "ID", "char(20)");
                obj.addField(1, "TYPE", "char(20)");
                obj.addField(2, "DATE_D", "char(20)");
                //obj.addField(3, "HEURE_D", "char(20)");
                //obj.addField(4, "PLACE", "char(20)");
                //obj.addField(5, "LIEU", "char(20)");


                int retVal = obj.export2Excel();

                if( retVal > 0)
                {
                    QMessageBox::information(this, tr("FAIS!"),
                                             QString(tr("%1 enregistrements exportés!")).arg(retVal)
                                             );
                }
                else
                {
                    QMessageBox::information(this, tr("not done!"),
                                             QString(tr(" enregistrements exportés!")));
                }
}

void gestionevenement::on_retour_evenement_clicked()
{
    hide();
    Rev= new MainWindow(this);
    Rev->show();
}
void gestionevenement::on_google_search_button_clicked()
{
searchEdit.show();
}
