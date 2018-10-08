#ifndef CONV_H
#define CONV_H

#include <QWidget>
#include "friendsmanager.h"

namespace Ui {
class conv;
}

class conv : public QWidget
{
    Q_OBJECT

public:
    explicit conv(QWidget *parent = nullptr);
    ~conv();

    void clean(void);
private slots:
    void on_callButton_clicked();

private:
    FriendsManager::FriendInfo  *_curFriendInfo;
    Ui::conv                    *ui;
};

#endif // CONV_H
