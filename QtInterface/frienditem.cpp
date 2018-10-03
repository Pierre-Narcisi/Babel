#include <QPainter>
#include <QStyle>
#include <QStyleOption>
#include <QMetaMethod>
#include <QBitmap>
#include <iostream>
#include "cache.h"
#include "singletons.h"
#include "frienditem.h"
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

FriendItem::FriendItem(FriendsManager::FriendInfo &n, QWidget *parent) :
    QWidget(parent),
    error(false),
    ready(false),
    myFriend(n),
    ui(new Ui::FriendItem)
{
    ui->setupUi(this);
    this->ui->FriendNameLabel->setText(myFriend.pseudo);
    this->ui->FriendImg->setPixmap(
                QPixmap::fromImage(
                    myFriend.icon.scaled(
                        this->ui->FriendImg->size(),
                        Qt::KeepAspectRatioByExpanding)));
    if (myFriend.connected == false) {
        auto w = new QWidget(this);
        w->setMaximumWidth(3);
        w->setStyleSheet("background-color: #00e600;");
        this->ui->horizontalLayout->insertWidget(0, w);
    }
}

FriendItem::~FriendItem()
{
    delete ui;
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

void FriendItem::actionClicked()
{

}

void FriendItem::paintEvent(QPaintEvent *e)
 {
    Q_UNUSED(e)

    QStyleOption opt;
    opt.init(this);
    QPainter p(this);
    this->style()->drawPrimitive(QStyle::PE_Widget, &opt, &p, this);
}

void FriendItem::mousePressEvent(QMouseEvent *)
{
    select();
}

void FriendItem::showEvent(QShowEvent *)
{
}
