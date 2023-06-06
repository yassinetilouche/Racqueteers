#include "statcours.h"
#include "ui_statcours.h"

statcours::statcours(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::statcours)
{
    ui->setupUi(this);
}

statcours::~statcours()
{
    delete ui;
}
