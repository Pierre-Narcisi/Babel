#include <QTimer>
#include "conv.h"
#include "ui_conv.h"
#include "singletons.h"

conv::conv(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::conv)
{
    ui->setupUi(this);

    QTimer::singleShot(0, [this] () {
        auto *l = Singletons::getListFriendWidget();
        QObject::connect(l, &ListFriends::onSelectChange, [this] (FriendItem *itm) {
            this->ui->labelPseudo->setText(itm->name);
        });
    });
}

conv::~conv()
{
    delete ui;
}
