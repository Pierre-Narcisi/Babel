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
