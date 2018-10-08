
#include <QTimer>
#include <QInputDialog>
#include <QMessageBox>
#include <QAction>
#include <QDir>
#include <QInputDialog>
#include <iostream>
#include <fstream>
#include <cstring>
#include "cache.h"
#include "clientmainwindows.h"
#include "ui_clientmainwindows.h"
#include "frienditem.h"
#include "login.h"
#include "singletons.h"
#include "settings.h"
#include "about.h"
#include "callform.h"
#include "login.h"
#include "usersettings.h"

ClientMainWindows::ClientMainWindows(QWidget *parent, common::Opts &opts) :
    QMainWindow(parent),
    _opts(opts),
    _srvCo(Singletons::getSrvCo()),
    ui(new Ui::ClientMainWindows)
{
    ui->setupUi(this);

    _srvCo.setHost(QString::fromStdString(_opts["host"]->as<common::Opts::String>()));
    _srvCo.setPort(_opts["port"]->as<common::Opts::Int>());
    _srvCo.setParent(nullptr);

    Singletons::setListFriendWidget(ui->listFriends);

    QObject::connect(&_srvCo, &client::protocol::ClientSender::disconnected, [this] {
        QMessageBox::critical(this, "Connection lost",
                              "Connection lost with the server\n"
                              "Babel will be closed");
        qApp->quit();
    });

    QObject::connect(&_srvCo, &client::protocol::ClientSender::onCallRequest,
                     [this] (QString username) {
        auto        &f = Singletons::getFriendsManager()[username.toStdString()];
        CallForm    *callWindow = new CallForm(nullptr, true);

        callWindow->setFriendInfo(&f);
        callWindow->show();
    });

    QAction *about = this->ui->menuBar->addAction("About");
    connect(about, &QAction::triggered, [this] () {
        About   aboutModal(this);

        aboutModal.exec();
    });

    connect(this->ui->listFriends, &ListFriends::onSelectChange, [this] (FriendItem *itm) {
        this->ui->listFriends->disconnectAll();
        (void) itm;
    });

    connect(this->ui->actionAdd_Friend, &QAction::triggered, [this] (bool) {
        babel::protocol::UpdateFriend    pack;

        pack.what = babel::protocol::UpdateFriend::What::NEW;
        QString name = QInputDialog::getText(this, "Add friend", "Enter your friend name:");
        std::strcpy(pack.username, name.toStdString().c_str());

        _srvCo.sendPacket(pack);
    });

    connect(this->ui->actionDelete_Friend, &QAction::triggered, [this] (bool) {
        babel::protocol::UpdateFriend    pack;

        pack.what = babel::protocol::UpdateFriend::What::ERASE;
        QString name = QInputDialog::getText(this, "Add friend", "Enter your friend name:");
        std::strcpy(pack.username, name.toStdString().c_str());

        _srvCo.sendPacket(pack);
    });

    connect(this->ui->actionSettings_2, &QAction::triggered, [this] (bool) {
        UserSettings s(this);

        auto ret = s.exec();
        if (ret == QDialog::Accepted) {
            auto    &settings = s.getSettings();
            
            if (settings.image.isEmpty() == false) {
                auto pack = babel::protocol::UpdateLogo::create(settings.image.size());

		auto str = settings.filename.toStdString();
		std::strncpy(pack->extend, str.substr(str.rfind('.'), str.size()).c_str(), 8);
		std::memcpy(pack.get() + 1, settings.image.data(), settings.image.size());
		_srvCo.sendPacket(*pack);
            }
            if (settings.password.isEmpty() == false) {
                babel::protocol::UpdateUser pack;

		std::strncpy(pack.password, settings.password.toStdString().c_str(), 128);
		std::strncpy(pack.newpassword, settings.newPassword.toStdString().c_str(), 128);
		_srvCo.sendPacket(pack);
            }
        }
    });

    connect(this->ui->actionDisconnect, &QAction::triggered, this, &ClientMainWindows::onDisconnectClicked);
}

ClientMainWindows::~ClientMainWindows()
{
    delete ui;
    Singletons::getSoundWrapper().stop();
    qApp->quit();
}

void ClientMainWindows::onDisconnectClicked(bool) {
    ui->listFriends->clean();
    Singletons::getFriendsManager().clean();
    ui->widget->clean();
    _srvCo.end();
    if (_srvCo.run()) {
        QMessageBox::critical(this, "Connection Error",
                            "Failed to connect to host ("
                            + QString::fromStdString(_opts["host"]->as<common::Opts::String>())
                            + ":"
                            + QString::number(_opts["port"]->as<common::Opts::Int>())
                            + ")\nTry with --host \"ip address\" and --port \"port number\"");
        qApp->quit();
    }
    auto *w = new login(this);
    w->setCannotAutoConnect(true);
    auto ret = w->exec();
    if (ret != QDialog::Accepted)
        this->close();
}

void ClientMainWindows::showEvent(QShowEvent *) {
    static bool first = true;

    if (!first)
        return;
    first = false;
    this->setEnabled(false);
    QTimer::singleShot(0, [this] () {
        if (_srvCo.run()) {
            QMessageBox::critical(this, "Connection Error",
                                "Failed to connect to host ("
                                + QString::fromStdString(_opts["host"]->as<common::Opts::String>())
                                + ":"
                                + QString::number(_opts["port"]->as<common::Opts::Int>())
                                + ")\nTry with --host \"ip address\" and --port \"port number\"");
            qApp->quit();
        }
        this->setEnabled(true);
        auto *w = new login(this);
        auto ret = w->exec();

        if (ret != QDialog::Accepted)
            this->close();
    });

    auto &s = Singletons::getSettings();

    auto    w = s["window"].toObject();
    if (w.empty())
        return;
    auto    winPos = w["pos"].toObject();
    auto    winSize = w["size"].toObject();

    this->move(winPos["x"].toInt(), winPos["y"].toInt());

    this->resize(winSize["w"].toInt(), winSize["h"].toInt());

}

void ClientMainWindows::closeEvent(QCloseEvent *)
{
    auto &s = Singletons::getSettings();

    s["window"] = QJsonObject {
        {"pos", QJsonObject {
            {"x", this->pos().x()},
            {"y", this->pos().y()}
        }},
        {"size", QJsonObject {
            {"w", this->width()},
            {"h", this->height()}
        }},
    };
    s.save();
}
