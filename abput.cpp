#include "abput.h"
#include "ui_abput.h"

Abput::Abput(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Abput)
{
    ui->setupUi(this);
}

Abput::~Abput()
{
    delete ui;
}
