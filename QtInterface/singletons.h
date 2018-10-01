#ifndef SINGLETONS_H
#define SINGLETONS_H

#include <QThreadPool>
#include "clientprotocol.h"
#include "settings.h"
#include "listfrienditem.h"

class Singletons
{
public:
    static QThreadPool*
                    getThreadPool(void);
    static client::protocol::ClientSender*
                    getSrvCo(void);
    static Settings *getSettings(void);

    static ListFriends  *getListFriendWidget(void);
    static void         setListFriendWidget(ListFriends *w);
private:
    Singletons() = default;

    static Singletons  &_get();

    ListFriends *_listFriendInstance = nullptr;
};

#endif // SINGLETONS_H
