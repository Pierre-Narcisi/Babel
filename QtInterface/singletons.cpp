#include "singletons.h"

QThreadPool *Singletons::getThreadPool(void)
{
    return QThreadPool::globalInstance();
}

client::protocol::ClientSender *Singletons::getSrvCo(void) {
    static client::Client                   _clt;
    static client::protocol::ClientSender   _m(_clt);

    return (&_m);
}

Settings *Singletons::getSettings(void) {
    static Settings _s;

    return (&_s);
}

ListFriends  *Singletons::getListFriendWidget(void) {
    auto &s = Singletons::_get();

    return s._listFriendInstance;
}

void         Singletons::setListFriendWidget(ListFriends *w) {
    auto &s = Singletons::_get();

    s._listFriendInstance = w;
}

Singletons  &Singletons::_get() {
    static Singletons _s;

    return _s;
}
