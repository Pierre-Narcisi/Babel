#ifndef FRIENDSMANAGER_H
#define FRIENDSMANAGER_H

#include <QObject>
#include <QImage>
#include <unordered_map>
#include <vector>
#include <memory>

class FriendsManager : public QObject
{
    Q_OBJECT
public:
    struct FriendInfo {
        QString username;
        QString pseudo;
        QImage  icon;
        struct {
            std::uint32_t   ip;
            std::uint16_t   port;
        }       udpInfos;
        bool    connected;
    };

    explicit FriendsManager(QObject *parent = nullptr);

    FriendInfo  &operator[](std::string const &name);
signals:
    void listUpdated(std::shared_ptr<std::vector<FriendInfo*>> list);
public slots:

private:
    using   Map = std::unordered_map<std::string, FriendInfo>;
    Map     _friends;
};



#endif // FRIENDSMANAGER_H
