#include "mwidget.h"
#include "ui_mwidget.h"

Mwidget::Mwidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Mwidget)
{
    ui->setupUi(this);
}

Mwidget::~Mwidget()
{
    delete ui;
}
