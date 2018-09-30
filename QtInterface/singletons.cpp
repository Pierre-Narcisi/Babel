#include "singletons.h"

QNetworkAccessManager *Singletons::getManager(void)
{
    static auto *_m = new QNetworkAccessManager();

    return (_m);
}

QThreadPool *Singletons::getThreadPool(void)
{
    return QThreadPool::globalInstance();
}

client::protocol::ClientSender *Singletons::getSrvCo(void) {
    static client::Client                   _clt;
    static client::protocol::ClientSender   _m(_clt);

    return (&_m);
}
