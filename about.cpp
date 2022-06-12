#include "about.h"
#include "ui_about.h"
#include <QHBoxLayout>


about::about(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::about)
{
    ui->setupUi(this);
    updateConfigUi();
}

about::~about()
{
    delete ui;
}

void about::updateConfigUi()
{
    _logo = new Logo(this);
    QHBoxLayout* mainLayout = new QHBoxLayout(ui->widget);
    mainLayout->addWidget(_logo);
}
