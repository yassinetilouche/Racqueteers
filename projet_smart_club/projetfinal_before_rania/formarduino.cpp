#include "formarduino.h"
#include "ui_formarduino.h"

FormArduino::FormArduino(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::FormArduino)
{
    ui->setupUi(this);
}

FormArduino::~FormArduino()
{
    delete ui;
}
