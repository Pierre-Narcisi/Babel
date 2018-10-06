#include "mainscreen.h"
#include "ui_mainscreen.h"

mainscreen::mainscreen(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::mainscreen)
{
    ui->setupUi(this);
}

mainscreen::~mainscreen()
{
    delete ui;
}
