#include <QTimer>
#include "conv.h"
#include "ui_conv.h"
#include "singletons.h"

conv::conv(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::conv)
{
    ui->setupUi(this);

    this->ui->labelPseudo->setText("");
    this->ui->labelName->setText("");
    QTimer::singleShot(0, [this] () {
        auto &l = Singletons::getListFriendWidget();
        QObject::connect(&l, &ListFriends::onSelectChange, [this] (FriendItem *itm) {
            this->ui->labelPseudo->setText(itm->myFriend.pseudo);
            this->ui->labelName->setText(itm->myFriend.username);
            try {
                auto f = Singletons::getFriendsManager()[itm->myFriend.username.toStdString()];
                this->ui->iconViewer->setPixmap(
                            QPixmap::fromImage(
                                f.icon.scaled(
                                    this->ui->iconViewer->size(),
                                    Qt::KeepAspectRatioByExpanding)));
            } catch (...) {}
        });
    });
}

conv::~conv()
{
    delete ui;
}

void conv::on_callButton_clicked()
{

}
