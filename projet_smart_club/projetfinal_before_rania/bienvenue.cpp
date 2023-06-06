#include "bienvenue.h"
#include "ui_bienvenue.h"

bienvenue::bienvenue(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::bienvenue)
{
    ui->setupUi(this);
}

bienvenue::~bienvenue()
{
    delete ui;
}
