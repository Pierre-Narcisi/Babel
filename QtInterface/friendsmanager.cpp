#include "friendsmanager.h"
#include "singletons.h"
#include "clientprotocol.h"

FriendsManager::FriendsManager(QObject *parent) : QObject(parent) {
    QObject::connect(&Singletons::getSrvCo(), &client::protocol::ClientSender::onFriendListChange,
                     [this] (std::vector<client::Friend> const &friends) {
        auto itList = std::make_shared<std::vector<FriendInfo*>>();

        itList->reserve(friends.size());
        for (auto &f: friends) {
            auto &it = _friends[f.username.toStdString()];

            itList->push_back(&it);
            it.username = f.username;
            it.pseudo = f.name;
            it.icon = QImage::fromData(
                        reinterpret_cast<const uchar*>(f.icon.data()),
                        f.icon.size());
            it.icon = it.icon.convertToFormat(QImage::Format_ARGB32);
            it.connected = f.state;
        }
        auto condition = [&itList] (Map::iterator const &it) {
            for (auto *avail: *itList) {
                if (avail->username.toStdString() == it->first)
                    return (false);
            }
            return (true);
        };
        auto iter = _friends.begin();
        auto endIter = _friends.end();
        for(; iter != endIter; ) {
            if (condition(iter)) {
                _friends.erase(iter++);
            } else {
                ++iter;
            }
        }
        emit listUpdated(itList);
    });
}

FriendsManager::FriendInfo  &FriendsManager::operator[](std::string const &name) {
    auto it = _friends.find(name);

    if (it == _friends.end()) {
        throw std::exception();
    } else {
        return (it->second);
    }
}

