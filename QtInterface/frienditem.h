#ifndef GAMEITEM_H
#define GAMEITEM_H

#include <QWidget>
#include <QNetworkAccessManager>
#include "Json/Entity.hpp"
#include "resoucesdownloader.h"
#include "hashchecker.h"

namespace Ui {
    class FriendItem;
}

class FriendItem : public QWidget
{
    Q_OBJECT
public:
    explicit FriendItem(json::Entity &item, QWidget *parent);
    ~FriendItem();

    json::Entity    getDataSheet(void);
    void            select(void);
    void            unSelect(void);
    void            actionClicked(void);
signals:
    void    onStateChange(FriendItem *me);
    void    onSelectChange(FriendItem *me, bool selected);

public:
    bool    error;
    bool    ready;

private slots:

private:
    void            _initIcon(void);
    virtual void    paintEvent(QPaintEvent *) final;
    virtual void    mousePressEvent(QMouseEvent *event) final;
    virtual void	showEvent(QShowEvent *event) final;

    Ui::FriendItem  *ui;
};

#endif // GAMEITEM_H
