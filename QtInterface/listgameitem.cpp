#include <iostream>
#include <QTimer>
#include <QStyle>
#include "cache.h"
#include "listgameitem.h"
#include "singletons.h"

ListGameItem::ListGameItem(QWidget *parent):
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
}

ListGameItem::~ListGameItem()
{
    clean();
}

void ListGameItem::addWidget(FriendItem *gitem)
{
    _lay->addWidget(gitem);
    _items.append(gitem);
    connect(gitem, &FriendItem::onSelectChange, this, &ListGameItem::onItemIsSelected);
    _resizeFrame();
    if (_items.count() == 1) {
        gitem->select();
    }
}

FriendItem *ListGameItem::getSelectedItem(void)
{
    return _selected;
}

void ListGameItem::disconnectAll(void)
{
    for (auto itm: _items) {
        disconnect(itm, &FriendItem::onStateChange, nullptr, nullptr);
    }
}

void ListGameItem::clean()
{
    for (auto itm: _items) {
        delete itm;
    }
    _items.clear();
}

void ListGameItem::_resizeFrame(void)
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

void    ListGameItem::onItemIsSelected(FriendItem *itmptr, bool selected)
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
