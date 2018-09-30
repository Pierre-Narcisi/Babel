
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
#include "about.h"
#include "login.h"

ClientMainWindows::ClientMainWindows(QWidget *parent, common::Opts &opts) :
    QMainWindow(parent),
    _opts(opts),
    _srvCo(Singletons::getSrvCo()),
    ui(new Ui::ClientMainWindows)
{
    ui->setupUi(this);

    _srvCo->setHost(QString::fromStdString(_opts["host"]->as<common::Opts::String>()));
    _srvCo->setPort(_opts["port"]->as<common::Opts::Int>());
    _srvCo->setParent(nullptr);
    QObject::connect(_srvCo, &client::protocol::ClientSender::disconnected, [this] {
        QMessageBox::critical(this, "Connection lost",
                              "Connection lost with the server\n"
                              "Babel will be closed");
        qApp->quit();
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

    /* Show 10 friends */
    for (auto i = 0; i < 10; i++) {
        auto *tmp = new FriendItem("Pote-" + QString::number(i), this);
        this->ui->listFriends->addWidget(tmp);
        tmp->select();
    }
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
        if (_srvCo->run()) {
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
}

void ClientMainWindows::closeEvent(QCloseEvent *)
{

}
