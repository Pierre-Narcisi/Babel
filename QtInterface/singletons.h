#ifndef SINGLETONS_H
#define SINGLETONS_H

#include <QThreadPool>
#include "clientprotocol.h"
#include "settings.h"

class Singletons
{
public:
    static QThreadPool*
                    getThreadPool(void);
    static client::protocol::ClientSender*
                    getSrvCo(void);
    static Settings *getSettings(void);
private:
    Singletons() = default;
};

#endif // SINGLETONS_H
