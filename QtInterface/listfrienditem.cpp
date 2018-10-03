#include <iostream>
#include <QTimer>
#include <QStyle>
#include "cache.h"
#include "listfrienditem.h"
#include "singletons.h"

ListFriends::ListFriends(QWidget *parent):
    QScrollArea(parent)
{
    this->setStyleSheet("background: rgb(230, 230, 230);");
    this->setFrameShape(QFrame::NoFrame);
    _hb = new QScrollBar(Qt::Vertical, this);
    _hb->setStyleSheet(Cache::getScrollBarStyle());
    this->setVerticalScrollBar(_hb);

    _frame = new QWidget(this);
    _lay = new QVBoxLayout(this);
    _lay->setContentsMargins(0, 0, 0, 0);
    _lay->setSpacing(0);
    _frame->setLayout(_lay);
    this->setWidget(_frame);

    connect(_hb, &QScrollBar::rangeChanged, [this] (int, int) {
        QTimer::singleShot(10, [this] () { _resizeFrame(); } );
    });

    connect(&Singletons::getFriendsManager(), &FriendsManager::listUpdated,
            [this] (std::shared_ptr<std::vector<FriendsManager::FriendInfo*>> list) {
        this->clean();
        for (auto *f: *list) {
            auto *itm = new FriendItem(*f, this);
            this->addWidget(itm);
        }
    });
}

ListFriends::~ListFriends()
{
    clean();
}

void ListFriends::addWidget(FriendItem *gitem)
{
    _lay->addWidget(gitem);
    _items.append(gitem);
    connect(gitem, &FriendItem::onSelectChange, this, &ListFriends::onItemIsSelected);
    _resizeFrame();
    if (_items.count() == 1) {
        gitem->select();
    }
}

FriendItem *ListFriends::getSelectedItem(void)
{
    return _selected;
}

void ListFriends::disconnectAll(void)
{
    for (auto itm: _items) {
        disconnect(itm, &FriendItem::onStateChange, nullptr, nullptr);
    }
}

void ListFriends::clean()
{
    for (auto itm: _items) {
        delete itm;
    }
    _items.clear();
}

void ListFriends::_resizeFrame(void)
{
    int     mt;
    int     mb;

    _lay->getContentsMargins(nullptr, &mt, nullptr, &mb);
    if (_items.isEmpty() == false) {
        int     h = (_items.count()) * static_cast<QWidget*>(_items[0])->height() + mb + mt;

        if (_hb->isVisible())
            _frame->resize(this->width() - _hb->width(), h);
        else
            _frame->resize(this->width(), h);
    }
}

void    ListFriends::onItemIsSelected(FriendItem *itmptr, bool selected)
{
    if (selected == false)
            return;
    for (FriendItem *itm: _items) {
        if (itm != itmptr) {
            itm->unSelect();
        }
    }
    _selected = itmptr;
    emit onSelectChange(_selected);
}
