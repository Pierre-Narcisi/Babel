#include <QTimer>
#include "conv.h"
#include "ui_conv.h"
#include "singletons.h"
#include "callform.h"
#include "listfrienditem.h"
#include "friendsmanager.h"

conv::conv(QWidget *parent) :
    QWidget(parent),
    _curFriendInfo(nullptr),
    ui(new Ui::conv)
{
    ui->setupUi(this);

    clean();
    QTimer::singleShot(0, [this] () {
        auto &l = Singletons::getListFriendWidget();
        QObject::connect(&l, &ListFriends::onSelectChange, [this] (FriendItem *itm) {
            this->ui->labelPseudo->setText(itm->myFriend.pseudo);
            this->ui->labelName->setText(itm->myFriend.username);
            try {
                auto &f = Singletons::getFriendsManager()[itm->myFriend.username.toStdString()];
                _curFriendInfo = &f;


                this->ui->callButton->setEnabled(true);
                this->ui->sendButton->setEnabled(true);
                this->ui->iconViewer->setPixmap(
                            QPixmap::fromImage(
                                f.icon.scaled(
                                    this->ui->iconViewer->size(),
                                    Qt::KeepAspectRatioByExpanding)));
            } catch (...) {
                this->ui->callButton->setEnabled(false);
                this->ui->sendButton->setEnabled(false);
            }
        });
    });

    QObject::connect(&Singletons::getFriendsManager(), &FriendsManager::listUpdated,
            [this] (std::shared_ptr<std::vector<FriendsManager::FriendInfo*>> list) {
        if (list->empty())
            this->clean();
    });

    QObject::connect(this->ui->callButton, &QPushButton::clicked, [this] {
        CallForm *callWindow = new CallForm(nullptr);

        callWindow->setFriendInfo(_curFriendInfo);
        callWindow->show();
    });
}

void conv::clean(void) {
    this->ui->labelPseudo->setText("");
    this->ui->labelName->setText("");
    this->ui->callButton->setEnabled(false);
    this->ui->sendButton->setEnabled(false);
}

conv::~conv()
{
    delete ui;
}

void conv::on_callButton_clicked()
{

}
