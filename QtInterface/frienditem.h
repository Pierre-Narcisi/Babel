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
    QString stateMessage;
    QString buttonText;
    QString speed;
    QString descriptionHtml;
    bool    error;
    int     progress;
    bool    checkingFiles;
    bool    ready;

private slots:

private:
    void        _initIcon(void);
    virtual void    paintEvent(QPaintEvent *) final;
    virtual void    mousePressEvent(QMouseEvent *event) final;
    virtual void	showEvent(QShowEvent *event) final;

    json::Entity    _data;
    Ui::FriendItem  *ui;
};

#endif // GAMEITEM_H
