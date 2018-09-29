#include <QPainter>
#include <QStyle>
#include <QStyleOption>
#include <QNetworkReply>
#include <QMetaMethod>
#include <iostream>
#include "cache.h"
#include "singletons.h"
#include "frienditem.h"
#include "hashchecker.h"
#include "resoucesdownloader.h"
#include "gamelauncher.h"
#include "ui_frienditem.h"

static inline QSize    operator+(QSize s, int toadd)
{
    s.setWidth(s.width() + toadd);
    s.setHeight(s.height() + toadd);
    return s;
}

static inline QSize    operator-(QSize s, int tosub)
{
    s.setWidth(s.width() - tosub);
    s.setHeight(s.height() - tosub);
    return s;
}

FriendItem::FriendItem(json::Entity &data, QWidget *parent) :
    QWidget(parent),
    stateMessage(""),
    buttonText(""),
    speed(""),
    descriptionHtml(""),
    error(false),
    progress(0),
    checkingFiles(true),
    ready(false),
    _data(data),
    ui(new Ui::FriendItem)
{
    ui->setupUi(this);
    this->ui->FriendNameLabel->setText(QString::fromStdString(data["name"].getData<json::String>().get()));
}

FriendItem::~FriendItem()
{
    delete ui;
}

json::Entity FriendItem::getDataSheet()
{
    return (_data);
}

void FriendItem::select()
{
    this->setProperty("selectedItem", true);
    this->ui->FriendNameLabel->setProperty("selectedItem", true);
    this->style()->polish(this);
    this->ui->FriendNameLabel->style()->polish(this->ui->FriendNameLabel);
    emit onSelectChange(this, true);
}

void FriendItem::unSelect()
{
    this->setProperty("selectedItem", {});
    this->ui->FriendNameLabel->setProperty("selectedItem", {});
    this->style()->polish(this);
    this->ui->FriendNameLabel->style()->polish(this->ui->FriendNameLabel);
    emit onSelectChange(this, false);
}


void FriendItem::_initIcon()
{

}

void FriendItem::actionClicked()
{

}

void FriendItem::paintEvent(QPaintEvent *)
 {
     QStyleOption opt;
     opt.init(this);
     QPainter p(this);
     this->style()->drawPrimitive(QStyle::PE_Widget, &opt, &p, this);
}

void FriendItem::mousePressEvent(QMouseEvent *)
{
    std::cout << "wtf\n";
    select();
}

void FriendItem::showEvent(QShowEvent *)
{
    _initIcon();
}
