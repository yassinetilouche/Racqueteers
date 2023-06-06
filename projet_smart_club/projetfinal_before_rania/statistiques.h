#ifndef STATISTIQUES_H
#define STATISTIQUES_H

#include <QDialog>
#include"qcustomplot.h"

#include<QSqlQuery>
#include<QSqlQueryModel>
namespace Ui {
class statistiques;
}

class statistiques : public QDialog
{
    Q_OBJECT

public:
    explicit statistiques(QWidget *parent = nullptr);
    ~statistiques();
    void makePlot();

private:
    Ui::statistiques *ui;
};

#endif // STATISTIQUES_H
