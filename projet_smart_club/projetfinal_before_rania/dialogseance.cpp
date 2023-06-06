#include "dialogseance.h"
#include "ui_dialogseance.h"

Dialogseance::Dialogseance(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::Dialogseance)
{
    ui->setupUi(this);
}

Dialogseance::~Dialogseance()
{
    delete ui;
}

