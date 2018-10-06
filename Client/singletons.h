#ifndef SINGLETONS_H
#define SINGLETONS_H


class SoundWrapper;
class QThreadPool;
namespace client { namespace protocol { class ClientSender; }}
class Settings;
class FriendsManager;
class ListFriends;

class Singletons
{
public:
    static QThreadPool&
                    getThreadPool(void);
    static client::protocol::ClientSender&
                    getSrvCo(void);
    static Settings &getSettings(void);
    static FriendsManager&
                    getFriendsManager(void);
    static SoundWrapper &getSoundWrapper(void);
    static ListFriends  &getListFriendWidget(void);
    static void         setListFriendWidget(ListFriends *w);
private:
    Singletons() = default;

    static Singletons  &_get();

    ListFriends *_listFriendInstance = nullptr;
};

#endif // SINGLETONS_H
