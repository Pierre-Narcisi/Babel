
#include <QTimer>
#include <QInputDialog>
#include <QMessageBox>
#include <QAction>
#include <QDir>
#include <iostream>
#include <fstream>
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

    QObject::connect(&_srvCo, &client::protocol::ClientSender::onPacketReceived,
                   [this] (babel::protocol::Packet &pack) {
        std::cerr << babel::protocol::Sender::humanReadable(pack.type) << std::endl;
    });

    QObject::connect(&_srvCo, &client::protocol::ClientSender::onCallRequest,
                     [this] (QString username) {
        auto &f = Singletons::getFriendsManager()[username.toStdString()];

        CallForm *callWindow = new CallForm(this, true);

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


}

ClientMainWindows::~ClientMainWindows()
{
    delete ui;
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
