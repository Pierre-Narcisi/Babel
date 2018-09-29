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

    QObject::connect(ui->checkBox, &QCheckBox::stateChanged, [this] (int state) {
        if (state == Qt::Checked)
            this->ui->pushButton->setText("Register");
        else
            this->ui->pushButton->setText("Login");
    });
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
        this->close();
    }
}

void login::on_login_finished(int)
{
    //exit(0);
}
