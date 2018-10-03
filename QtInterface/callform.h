#ifndef CALLFORM_H
#define CALLFORM_H

#include <QDialog>
#include "friendsmanager.h"

namespace Ui {
class CallForm;
}

class CallForm : public QDialog
{
    Q_OBJECT

public:
    explicit CallForm(QWidget *parent = 0);
    ~CallForm();

    void    setFriendInfo(FriendsManager::FriendInfo *f);
private slots:
    void    onEndClicked(void);
private:
    void    showEvent(QShowEvent *e);
    void    _paintBlurImage(void);

    Ui::CallForm                *ui;
    FriendsManager::FriendInfo  *_f;
};

#endif // CALLFORM_H
