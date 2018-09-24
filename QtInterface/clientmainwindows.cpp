#include <QListWidgetItem>
#include <QInputDialog>
#include <QMessageBox>
#include <QAction>
#include <QDir>
#include <iostream>
#include <fstream>
#include "Json/Parser.hpp"
#include "cache.h"
#include "clientmainwindows.h"
#include "ui_clientmainwindows.h"
#include "frienditem.h"
#include "login.h"
#include "singletons.h"
#include "about.h"
#include "login.h"

ClientMainWindows::ClientMainWindows(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::ClientMainWindows)
{
    login w;
    w.exec();

    ui->setupUi(this);

    auto    update = this->ui->menuBar->addAction("Update");
    connect(update, &QAction::triggered, [this, update] () {
            update->setEnabled(false);
            QTimer::singleShot(1000, [update] () {
                update->setEnabled(true);
            });
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

    auto game = json::Entity::newObject();

    game["name"] = "Ah";
    auto tmp = new FriendItem(game, this);
    this->ui->listFriends->addWidget(tmp);
    tmp->select();
}

ClientMainWindows::~ClientMainWindows()
{
    delete ui;
}

void ClientMainWindows::closeEvent(QCloseEvent *)
{
    auto winSettings = json::Entity::newObject();

    winSettings["position"] = json::makeObject {
        {"x", this->pos().x()},
        {"y", this->pos().y()}
    };
    winSettings["size"] = json::makeObject {
        {"w", this->width()},
        {"h", this->height()}
    };
    _settings["window"] = winSettings;
}
