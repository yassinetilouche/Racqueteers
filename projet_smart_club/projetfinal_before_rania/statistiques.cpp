#include "statistiques.h"
#include "ui_statistiques.h"

statistiques::statistiques(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::statistiques)
{
    ui->setupUi(this);
    statistiques::makePlot();
}

statistiques::~statistiques()
{
    delete ui;
}
void statistiques::makePlot()
{    QSqlQuery qry;

     int t11=0;

       int t21=0;

         int t31=0;


   qry.prepare("select * from seances where lieu = 'SOUSSE'  ");
     if (qry.exec())
     {
         while (qry.next())
         {
            t11++;


       }
     }
     qry.prepare("select * from seances where lieu = 'ARIANA'  ");
       if (qry.exec())
       {
           while (qry.next())
           {
              t21++;


         }
       }
       qry.prepare("select * from seances where lieu = 'TUNIS'  ");
         if (qry.exec())
         {
             while (qry.next())
             {
                t31++;


           }
         }


    // set dark background gradient:
    QLinearGradient gradient(0, 0, 0, 400);
    gradient.setColorAt(0, QColor(90, 90, 90));
    gradient.setColorAt(0.38, QColor(105, 105, 105));
    gradient.setColorAt(1, QColor(70, 70, 70));
    ui->customPlot->setBackground(QBrush(gradient));


    QCPBars *m2 = new QCPBars(ui->customPlot->xAxis, ui->customPlot->yAxis);
    QCPBars *m1 = new QCPBars(ui->customPlot->xAxis, ui->customPlot->yAxis);
     m2->setAntialiased(false);
    m1->setAntialiased(false);
     m2->setStackingGap(1);
    m1->setStackingGap(1);
    // set names and colors:
    m1->setName("");
    m1->setPen(QPen(QColor(20,61,89).lighter(170)));
    m1->setBrush(QColor(20,61,89));
    m2->setName("");
    m2->setPen(QPen(QColor(244,180,26).lighter(150)));
    m2->setBrush(QColor(244,180,26));

    // stack bars on top of each other:
    m2->moveAbove(m1);


    // prepare x axis with country labels:
    QVector<double> ticks;
    QVector<QString> labels;
    ticks << 1 << 2 << 3   ;
    labels << "SOUSSE" << "ARIANA" << "TUNIS"   ;
    QSharedPointer<QCPAxisTickerText> textTicker(new QCPAxisTickerText);
    textTicker->addTicks(ticks, labels);
    ui->customPlot->xAxis->setTicker(textTicker);
    ui->customPlot->xAxis->setTickLabelRotation(60);
         ui->customPlot->xAxis->setLabel("LIEU");
    ui->customPlot->xAxis->setSubTicks(false);
    ui->customPlot->xAxis->setTickLength(0, 4);
    ui->customPlot->xAxis->setRange(0, 8);
    ui->customPlot->xAxis->setBasePen(QPen(Qt::white));
    ui->customPlot->xAxis->setTickPen(QPen(Qt::white));
    ui->customPlot->xAxis->grid()->setVisible(true);
    ui->customPlot->xAxis->grid()->setPen(QPen(QColor(130, 130, 130), 0, Qt::DotLine));
    ui->customPlot->xAxis->setTickLabelColor(Qt::white);
    ui->customPlot->xAxis->setLabelColor(Qt::white);

    // prepare y axis:
    ui->customPlot->yAxis->setRange(0, 5);
    ui->customPlot->yAxis->setPadding(30); // a bit more space to the left border
    ui->customPlot->yAxis->setLabel("NUMBER OF SEANCES");
    ui->customPlot->yAxis->setBasePen(QPen(Qt::white));
    ui->customPlot->yAxis->setTickPen(QPen(Qt::white));
    ui->customPlot->yAxis->setSubTickPen(QPen(Qt::white));
    ui->customPlot->yAxis->grid()->setSubGridVisible(true);
    ui->customPlot->yAxis->setTickLabelColor(Qt::white);
    ui->customPlot->yAxis->setLabelColor(Qt::white);
    ui->customPlot->yAxis->grid()->setPen(QPen(QColor(130, 130, 130), 0, Qt::SolidLine));
    ui->customPlot->yAxis->grid()->setSubGridPen(QPen(QColor(130, 130, 130), 0, Qt::DotLine));

    // Add data:
    QVector<double> m1data ;
    m1data  << t11 << t21 << t31   ;


   m1->setData(ticks, m1data);


    // setup legend:
    ui->customPlot->legend->setVisible(true);
    ui->customPlot->axisRect()->insetLayout()->setInsetAlignment(0, Qt::AlignTop|Qt::AlignHCenter);
    ui->customPlot->legend->setBrush(QColor(255, 255, 255, 100));
    ui->customPlot->legend->setBorderPen(Qt::NoPen);
    QFont legendFont = font();
    legendFont.setPointSize(10);
    ui->customPlot->legend->setFont(legendFont);
    ui->customPlot->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom);
}
