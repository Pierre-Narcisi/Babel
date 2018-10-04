#include <QDebug>
#include <string>
#include <cstring>
#include <QCryptographicHash>
#include <QMessageBox>
#include "login.h"
#include "singletons.h"
#include "ui_login.h"
#include "settings.h"
#include "clientprotocol.h"

login::login(QWidget *parent) :
    QDialog(parent),
    _cr(Singletons::getSettings()["credentials"].toObject()),
    ui(new Ui::login)
{
    ui->setupUi(this);

    this->setAttribute(Qt::WA_DeleteOnClose, true);
    ui->lineEdit_name->setText(_cr["username"].toString());
    ui->lineEdit_password->setText(_cr["password"].toString());
    ui->lineEdit_name->setMaxLength(sizeof(babel::protocol::Connect::username));
    ui->lineEdit_password->setMaxLength(sizeof(babel::protocol::Connect::password));
    ui->checkBoxRemember->setChecked(!ui->lineEdit_password->text().isEmpty());

    QObject::connect(ui->checkBox, &QCheckBox::stateChanged, [this] (int state) {
        if (state == Qt::Checked)
            this->ui->pushButton->setText("Register");
        else
            this->ui->pushButton->setText("Login");
    });

    QObject::connect(ui->checkBoxRemember, &QCheckBox::stateChanged, [this] (int state) {
        if (state == Qt::Checked)
            _cr["password"] = ui->lineEdit_password->text().toStdString().c_str();
        else
            _cr["password"] = "";
    });

    QObject::connect(&Singletons::getSrvCo(), &client::protocol::ClientSender::onPacketReceived,
                     this, &login::onPacketReceived);
}

void login::onPacketReceived(babel::protocol::Packet &pack) {
    auto &p = reinterpret_cast<babel::protocol::Respond&>(pack);

    if ((pack.type == babel::protocol::Packet::Type::Respond)
    && (p.previous == babel::protocol::Packet::Type::Connect)) {
        this->setEnabled(true);
        if (p.respond == p.KO) {
            QMessageBox::information(this, "Connection failed", QString::fromLatin1(p.data));
        } else {
            this->accept();
        }
    }
}

login::~login()
{
    delete ui;
}

void login::on_pushButton_clicked()
{
    auto &srvCo = Singletons::getSrvCo();

    QString name = ui->lineEdit_name->text();
    QString password = ui->lineEdit_password->text();
    babel::protocol::Connect    pack;

    if (ui->checkBox->isChecked()) {
        pack.connectionType = babel::protocol::Connect::Type::CREATE;
    } else {
        pack.connectionType = babel::protocol::Connect::Type::CONNECT;
    }
    std::strcpy(pack.username, name.toStdString().c_str());
    std::strcpy(pack.password, password.toStdString().c_str());

    srvCo.sendPacket(pack);
    this->setEnabled(false);

    _cr["username"] = name;
    if (ui->checkBoxRemember->isChecked())
        _cr["password"] = password;
}

void login::on_login_finished(int)
{
    Singletons::getSettings()["credentials"] = _cr;
}
