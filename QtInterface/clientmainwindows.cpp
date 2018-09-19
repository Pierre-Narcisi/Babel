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
#include "singletons.h"
#include "about.h"

ClientMainWindows::ClientMainWindows(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::ClientMainWindows)
{
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

    connect(this->ui->gameActionButton, &QPushButton::clicked, [this] () {
        this->ui->gameActionButton->setEnabled(false);
        this->ui->listGames->getSelectedItem()->actionClicked();
    });

    connect(this->ui->listGames, &ListGameItem::onSelectChange, [this] (FriendItem *itm) {
        this->ui->listGames->disconnectAll();
        (void) itm;
    });

    auto game = json::Entity::newObject();

    game["name"] = "Ah";
    auto tmp = new FriendItem(game, this);
    this->ui->listGames->addWidget(tmp);
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
