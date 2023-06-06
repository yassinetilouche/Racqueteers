#include "performance.h"
#include <QSqlQuery>
#include <QtDebug>
#include <QDate>
#include <QObject>
#include <QSqlQueryModel>
#include <iostream>
#include <QSqlError>
#include <string>
#include "GestionAdherent.h"
#include <QMessageBox>
performance::performance()
{
IdAd='0';
}
performance::performance(int IdPerfo,int IdAd,QDate DatePerfo,int servespeed1,int servespeed2,int servespeed3)
{   this->IdAd=IdAd;
    this->IdPerfo=IdPerfo;
    this->DatePerfo=DatePerfo;
    this->servespeed1=servespeed1;
    this->servespeed2=servespeed2;
    this->servespeed3=servespeed3;}
int performance::getidperfo(){return IdPerfo;}
int performance::getdateperfot(){return datperfot;}
int performance::getservicetest(){return servicetest;}

void performance::setidperfo(int id){this->IdPerfo=id;}
bool performance::ajouter(){

    QSqlQuery query;
    QDate datenow;
       //int IdPerfo_string =int::number(IdPerfo);
       //int IdAd_string =int::number(IdAd);
        //std::cout<<IdPerfo;
        //std::cout<<IdAd;
        //std::cout<<servespeed1;

       query.prepare("INSERT INTO PERFORMANCE (IdPerfo,IdAD,DatePerfo, servespeed1,servespeed2,servespeed3) "
                     "VALUES (:IdPerfo,:IdAd,:DatePerfo, :servespeed1,:servespeed2,:servespeed3)");
       query.bindValue(":IdPerfo", IdPerfo);
       query.bindValue(":IdAd", IdAd);
       query.bindValue(":DatePerfo",DatePerfo);
       query.bindValue(":servespeed1",servespeed1 );
       query.bindValue(":servespeed2", servespeed2);
       query.bindValue(":servespeed3",servespeed3);
       if(servespeed1==  NULL || IdPerfo==NULL || IdAd==NULL )
       {
           QMessageBox::critical(nullptr, QObject::tr("Verification d'ajout"),
                QObject::tr("Erreur champ vid_Categoriee!.\n"
                            "Click Cancel to exit."), QMessageBox::Cancel);
           return false;
       }
       if(DatePerfo>datenow.currentDate() || servespeed1>500 )
       { if(DatePerfo>datenow.currentDate())
           {
           /*QMessageBox::critical(nullptr, QObject::tr("Verification d'ajout"),
                QObject::tr("numero de telphone non valide !.\n"
                            "Click Cancel to exit."), QMessageBox::Cancel);*/
           datperfot=1;

       }
           if(servespeed1>500)
           {
               servicetest=1;

           }

        return false;
}

        qDebug()<<query.lastError().text();
    return query.exec();

}
QSqlQueryModel*  performance::affection()
{
    QSqlQuery query;
    QSqlQueryModel* model = new QSqlQueryModel();

       //int IdPerfo_string =int::number(IdPerfo);
       //int IdAd_string =int::number(IdAd);
        //std::cout<<IdPerfo;
        //std::cout<<IdAd;
        //std::cout<<servespeed1;

       query.prepare("INSERT INTO Adherent_perfo (IdPerfo,Id_Adherent,DatePerfo, servespeed1,servespeed2,servespeed3) "
                     "VALUES (:IdPerfo,:Id_adherent,:DatePerfo, :servespeed1,:servespeed2,:servespeed3)");
       query.bindValue(":IdPerfo", IdPerfo);
       query.bindValue(":Id_adherent", IdAd);
       query.bindValue(":DatePerfo",DatePerfo);
       query.bindValue(":servespeed1",servespeed1 );
       query.bindValue(":servespeed2", servespeed2);
       query.bindValue(":servespeed3",servespeed3);
       query.exec();
       QSqlQuery query2;
       QString id_string =QString::number(IdAd);
       //QString num_tel_string =QString::number(num_tel);
      // qDebug()<<id_string;
       //query2.prepare("Update adherent_perfo set adherent_perfo.nom=Adherent.nom ,adherent_perfo.prenom=Adherent.prenom,adherent_perfo.sexe=Adherent.sexe FROM adherent where adherent.Id_Adherent=adherent_perfo.Id_adherent ");
       //query2.bindValue(":id_adherent", IdAd);
       model->setQuery("SELECT A.nom,A.prenom, A.Id_Adherent, P.servespeed1,P.servespeed2,P.servespeed3 From Adherent A FULL JOIN Performance P on A.Id_Adherent=P.IdAd");
       if(!query2.exec()){
           qDebug()<< query2.lastError().text();
       }
       query2.exec();
       return model;

}
QSqlQueryModel* performance::afficher_performance()
{
 QSqlQueryModel* model = new QSqlQueryModel();
 model->setQuery("SELECT* FROM performance");


    return model;
}
bool performance::modifier()
{
    QSqlQuery query;
    //int idPerfo_string =int::number(IdPerfo);
    //int idAd_string =int::number(IdAd);
    //std::cout<<IdPerfo;
    //std::cout<<IdAd;
    //std::cout<<servespeed1;
    query.prepare("UPDATE performance SET IdAD= :IdAD,DatePerfo= :DatePerfo,servespeed1=:servespeed1,servespeed2=:servespeed2,servespeed3=:servespeed3 WHERE idperfo= :idperfo  ");
    query.bindValue(":IdPerfo", IdPerfo);
    query.bindValue(":IdAd", IdAd);
    query.bindValue(":DatePerfo",DatePerfo);
    query.bindValue(":servespeed1",servespeed1 );
    query.bindValue(":servespeed2", servespeed2);
    query.bindValue(":servespeed3",servespeed3);
    if(!query.exec()){
        qDebug()<< query.lastError().text();
    }
    return query.exec();

}
bool performance::supprimer(int Idperfo)
{
    QSqlQuery query;

       query.prepare("DELETE from performance where Idperfo=:Idperfo");
       query.bindValue(":Idperfo", Idperfo);



    return query.exec();

}
QSqlQueryModel *performance::sortserve1()
{


    QSqlQueryModel * model=new QSqlQueryModel();

    model->setQuery("select * from performance ORDER BY servespeed1 DESC ");



    return model;
}
QSqlQueryModel *performance::sortserve2()
{


    QSqlQueryModel * model=new QSqlQueryModel();

    model->setQuery("select * from performance ORDER BY servespeed2 DESC ");



    return model;
}
QSqlQueryModel *performance::sortserve3()
{


    QSqlQueryModel * model=new QSqlQueryModel();

    model->setQuery("select * from performance ORDER BY servespeed3 DESC ");




    return model;
}
QSqlQueryModel *performance::stats()
{
    QSqlQueryModel * model1= new QSqlQueryModel();

    model1->setQuery("SELECT IDAD,IDperfo,servespeed2/ servespeed1 as serve_dev from performance ");
    int avg= model1->data(model1->index(0, 0)).toInt();
    std::cout<<avg;
   // QSqlQueryModel * model2= new QSqlQueryModel();
    //model->setQuery("SELECT  FROM performance");

        return model1;
}
void performance::statt(QCustomPlot *customPlot)
{
    QSqlQuery query,query1;
    // set dark background gradient:
    QLinearGradient gradient(0, 0, 0, 400);
    gradient.setColorAt(0, QColor(90, 90, 90));
    gradient.setColorAt(0.38, QColor(105, 105, 105));
    gradient.setColorAt(1, QColor(70, 70, 70));
    customPlot->clearPlottables();
    customPlot->clearGraphs();
    customPlot->replot();

    customPlot->setBackground(QBrush(gradient));

    // create empty bar chart objects:
   // QCPBars *regen = new QCPBars(customPlot->xAxis, customPlot->yAxis);
   // QCPBars *nuclear = new QCPBars(customPlot->xAxis, customPlot->yAxis);
    QCPBars *fossil = new QCPBars(customPlot->xAxis, customPlot->yAxis);
  //  regen->setAntialiased(false); // gives more crisp, pixel aligned bar borders
  //  nuclear->setAntialiased(false);
    fossil->setAntialiased(false);
  //  regen->setStackingGap(1);
    //nuclear->setStackingGap(1);
    fossil->setStackingGap(1);
    // set names and colors:
    fossil->setName("vitesse service ");
    fossil->setPen(QPen(QColor(111, 9, 176).lighter(170)));
    fossil->setBrush(QColor(111, 9, 176));
  //  nuclear->setName("Nuclear");
  //  nuclear->setPen(QPen(QColor(250, 170, 20).lighter(150)));
  //  nuclear->setBrush(QColor(250, 170, 20));
   // regen->setName("Regenerative");
  //  regen->setPen(QPen(QColor(0, 168, 140).lighter(130)));
  //  regen->setBrush(QColor(0, 168, 140));
    // stack bars on top of each other:
  //  nuclear->moveAbove(fossil);
 //   regen->moveAbove(nuclear);

    // prepare x axis with country labels:
    QVector<double> ticks;
    QVector<QString> labels;
    query.prepare("SELECT COUNT(DISTINCT idperfo) FROM performance where SERVESPEED1 between 0 and 50");
    query.exec();
    int i;
    while(query.next())
    {
        i=query.value(0).toInt();
    }
    query.prepare("SELECT COUNT(DISTINCT idperfo) FROM performance where SERVESPEED1 between 500 and 100");
    query.exec();
    int j;
    while(query.next())
    {
        j=query.value(0).toInt();
    }
    query.prepare("SELECT COUNT(DISTINCT idperfo) FROM performance where SERVESPEED1 > 100");
    query.exec();
    int k;
    while(query.next())
    {
        k=query.value(0).toInt();
    }





    ticks << 1 << 2 << 3 ;
    labels << "[ 0 ,50 DT ]" << "[ 50 ,100 ]"<<"Plus que 100 DT" ;
    QSharedPointer<QCPAxisTickerText> textTicker(new QCPAxisTickerText);
    textTicker->addTicks(ticks, labels);
    customPlot->xAxis->setTicker(textTicker);
    customPlot->xAxis->setTickLabelRotation(60);
    customPlot->xAxis->setSubTicks(false);
    customPlot->xAxis->setTickLength(0, 4);
    customPlot->xAxis->setRange(0, 8);
    customPlot->xAxis->setBasePen(QPen(Qt::white));
    customPlot->xAxis->setTickPen(QPen(Qt::white));
    customPlot->xAxis->grid()->setVisible(true);
    customPlot->xAxis->grid()->setPen(QPen(QColor(130, 130, 130), 0, Qt::DotLine));
    customPlot->xAxis->setTickLabelColor(Qt::white);
    customPlot->xAxis->setLabelColor(Qt::white);

    // prepare y axis:
    customPlot->yAxis->setRange(0, 20);
    customPlot->yAxis->setPadding(5); // a bit more space to the left border
    customPlot->yAxis->setLabel("Intervalle des vitesses des services");
    customPlot->yAxis->setBasePen(QPen(Qt::white));
    customPlot->yAxis->setTickPen(QPen(Qt::white));
    customPlot->yAxis->setSubTickPen(QPen(Qt::white));
    customPlot->yAxis->grid()->setSubGridVisible(true);
    customPlot->yAxis->setTickLabelColor(Qt::white);
    customPlot->yAxis->setLabelColor(Qt::white);
    customPlot->yAxis->grid()->setPen(QPen(QColor(130, 130, 130), 0, Qt::SolidLine));
    customPlot->yAxis->grid()->setSubGridPen(QPen(QColor(130, 130, 130), 0, Qt::DotLine));

    // Add data:
    QVector<double> fossilData, nuclearData, regenData;
    fossilData  << i << j << k;
   // nuclearData << 0.08*10.5 << 0.12*5.5 << 0.12*5.5 << 0.40*5.8 << 0.09*5.2 << 0.00*4.2 << 0.07*11.2;
    regenData   << 0.06*10.5 << 0.05*5.5 << 0.04*5.5 << 0.06*5.8 << 0.02*5.2 << 0.07*4.2 << 0.25*11.2;
    fossil->setData(ticks, fossilData);
  //  nuclear->setData(ticks, nuclearData);
 //   regen->setData(ticks, regenData);

    // setup legend:
    customPlot->legend->setVisible(true);
    customPlot->axisRect()->insetLayout()->setInsetAlignment(0, Qt::AlignTop|Qt::AlignHCenter);
    customPlot->legend->setBrush(QColor(255, 255, 255, 100));
    customPlot->legend->setBorderPen(Qt::NoPen);
    QFont legendFont = QFont();
    legendFont.setPointSize(10);
    customPlot->legend->setFont(legendFont);
    customPlot->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom);

}
