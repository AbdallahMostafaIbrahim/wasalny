#include "createnewcity.h"
#include "ui_createnewcity.h"

createnewcity::createnewcity(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::createnewcity)
{
    ui->setupUi(this);
}

createnewcity::~createnewcity()
{
    delete ui;
}

void createnewcity::on_OKButton_clicked()
{
    // if cityName DNE, create new city


    //if exists, create new path

    hide();
}

