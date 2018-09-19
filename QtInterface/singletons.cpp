#include "singletons.h"

QNetworkAccessManager *Singletons::getManager(void)
{
    static auto _m = new QNetworkAccessManager();

    return (_m);
}

QThreadPool *Singletons::getThreadPool(void)
{
    return QThreadPool::globalInstance();
}
