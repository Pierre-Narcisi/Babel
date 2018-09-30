#include <QDebug>
#include <string>
#include <cstring>
#include <QCryptographicHash>
#include <QMessageBox>
#include "login.h"
#include "singletons.h"
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

    QObject::connect(Singletons::getSrvCo(), &client::protocol::ClientSender::onPacketReceived,
                     [this] (babel::protocol::Packet &pack) {
        auto &p = reinterpret_cast<babel::protocol::Respond&>(pack);

        if ((pack.type == babel::protocol::Packet::Type::Respond)
        && (p.previous == babel::protocol::Packet::Type::Connect)) {
            this->setEnabled(true);
            if (p.respond == p.KO) {
                QMessageBox::information(this, "Connection failed", "Authentification failed, check your credentials.");
            } else {
                this->accept();
            }
        }
    });
}

login::~login()
{
    delete ui;
}

void login::on_pushButton_clicked()
{
    auto *srvCo = Singletons::getSrvCo();
//  QCryptographicHash  passHashor(QCryptographicHash::Sha3_512);
//  passHashor.addData(ui->lineEdit_password->text().toLatin1());

    QString name = ui->lineEdit_name->text();
    QString password = ui->lineEdit_password->text().toLatin1(); //passHashor.result().toBase64();
    babel::protocol::Connect    pack;

    std::strcpy(pack.username, name.toStdString().c_str());
    std::strcpy(pack.password, password.toStdString().c_str());
    pack.needRegister = ui->checkBox->isChecked();

    srvCo->sendPacket(pack);
    this->setEnabled(false);
}

void login::on_login_finished(int)
{
    //exit(0);
}
