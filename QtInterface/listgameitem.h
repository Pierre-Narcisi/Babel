#ifndef LISTGAMEITEM_H
#define LISTGAMEITEM_H

#include <QVBoxLayout>
#include <QScrollArea>
#include <QScrollBar>
#include "frienditem.h"

class ListGameItem : public QScrollArea
{
    Q_OBJECT
public:
    explicit ListGameItem(QWidget *parent = nullptr);
    ~ListGameItem();

    void        addWidget(FriendItem *);
    FriendItem    *getSelectedItem(void);
    void        disconnectAll(void);
    void        clean(void);

private:
    QList<FriendItem*>    _items;
    QWidget             *_frame = nullptr;
    QVBoxLayout         *_lay = nullptr;
    QScrollBar          *_hb = nullptr;
    FriendItem            *_selected = nullptr;

    void _resizeFrame(void);

signals:
    void    onSelectChange(FriendItem *itm);

private slots:
    void    onItemIsSelected(FriendItem *itmptr, bool selected);
};

#endif // LISTGAMEITEM_H
