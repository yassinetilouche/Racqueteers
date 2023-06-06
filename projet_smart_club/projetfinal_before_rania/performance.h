#ifndef PERFORMANCE_H
#define PERFORMANCE_H

#include <QMainWindow>
#include <QObject>
#include <QDate>
#include <QSharedDataPointer>
#include <QWidget>
#include <QSqlQueryModel>
#include "qcustomplot.h"

class performanceData;

class performance
{

public:
    performance();
    performance(int,int,QDate,int,int,int);
    int getidperfo();
    int getidad();
    QDate getdateperfo();
    int getservespeed1();
    int getservespeed2();
    int getservespeed3();
    int getdateperfot();
    int getservicetest();
    void setidperfo(int);
    bool ajouter();
    QSqlQueryModel* affection();
    QSqlQueryModel* afficher_performance();
    bool modifier();
    bool supprimer(int);
    QSqlQueryModel*  sortserve1();
    QSqlQueryModel*  sortserve2();
    QSqlQueryModel*  sortserve3();
    QSqlQueryModel*  stats();
    void statt(QCustomPlot *customPlot);

private:


    int IdAd,IdPerfo,servespeed1,servespeed2,servespeed3;
    QDate DatePerfo;
    int datperfot,servicetest;
};

#endif // PERFORMANCE_H
