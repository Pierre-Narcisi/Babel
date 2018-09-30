#ifndef SINGLETONS_H
#define SINGLETONS_H

#include <QNetworkAccessManager>
#include <QThreadPool>
#include "clientprotocol.h"

class Singletons
{
public:
    static QNetworkAccessManager*
                    getManager(void);
    static QThreadPool*
                    getThreadPool(void);
    static client::protocol::ClientSender*
                    getSrvCo(void);
private:
    Singletons() = default;
};

#endif // SINGLETONS_H
