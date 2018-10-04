#ifndef CALLFORM_H
#define CALLFORM_H

#include <QDialog>
#include "friendsmanager.h"
#include "clientprotocol.h"

namespace Ui {
class CallForm;
}

class CallForm : public QDialog
{
    Q_OBJECT

public:
    explicit CallForm(QWidget *parent = 0, bool isDemand = false);
    ~CallForm();

    void    setFriendInfo(FriendsManager::FriendInfo *f);
private slots:
    void    onEndClicked(void);
    void    onRejectClicked(void);
    void    onAcceptClicked(void);
    void    onPacketReceived(babel::protocol::Packet &packet);
    void    onCallEnd(QString name);
private:
    virtual void    showEvent(QShowEvent *e);
    virtual void    paintEvent(QPaintEvent *e);
    void    _paintBlurImage(void);
    void    _registerCallEnd(void);

    FriendsManager::FriendInfo  *_f;
    bool                        _isDemand;
    bool                        _isInit = false;
    Ui::CallForm                *ui;
};

#endif // CALLFORM_H
