#ifndef GAMEITEM_H
#define GAMEITEM_H

#include <QWidget>
#include <QNetworkAccessManager>
#include "friendsmanager.h"

namespace Ui {
    class FriendItem;
}

class FriendItem : public QWidget
{
    Q_OBJECT
public:
    explicit FriendItem(FriendsManager::FriendInfo &n, QWidget *parent);
    ~FriendItem();

    void            select(void);
    void            unSelect(void);
    void            actionClicked(void);
signals:
    void    onStateChange(FriendItem *me);
    void    onSelectChange(FriendItem *me, bool selected);

public:
    bool    error;
    bool    ready;

    FriendsManager::FriendInfo  &myFriend;

private slots:

private:
    virtual void    paintEvent(QPaintEvent *) final;
    virtual void    mousePressEvent(QMouseEvent *event) final;
    virtual void	showEvent(QShowEvent *event) final;

    Ui::FriendItem  *ui;
};

#endif // GAMEITEM_H
