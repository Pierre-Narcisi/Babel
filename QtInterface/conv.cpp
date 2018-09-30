#include "conv.h"
#include "ui_conv.h"

conv::conv(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::conv)
{
    ui->setupUi(this);
}

conv::~conv()
{
    delete ui;
}
