#include <QDebug>
#include <string>
#include "login.h"
#include "ui_login.h"

login::login(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::login)
{
    _register = 0;
    ui->setupUi(this);
}

login::~login()
{
    delete ui;
}

void login::on_pushButton_clicked()
{
    QString name = ui->lineEdit_name->text();
    QString password = ui->lineEdit_password->text();
    qDebug() << name;
    qDebug() << password;
    if (name == "test" && password == "test") {
        this->~login();
    }
}

void login::on_login_finished(int result)
{
    exit(0);
}
