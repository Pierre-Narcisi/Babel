#include "about.h"
#include "ui_about.h"
#include "version.h"

About::About(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::About)
{
    ui->setupUi(this);

    this->ui->labelVersion->setText(Version::toString());
    connect(ui->buttonOk, &QPushButton::clicked, this, &About::onOkClick);
}

About::~About()
{
    delete ui;
}

void About::onOkClick(bool)
{
    this->close();
}
