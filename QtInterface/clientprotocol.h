/*
** EPITECH PROJECT, 2018
** babel
** File description:
** ClientProtocol.hpp
*/

#pragma once

#include <QObject>
#include <string>
#include <vector>

#include "Network/QtSocket.hpp"
#include "Protocol/Protocol.h"
#include "Chopper/Chopper.hpp"

namespace client {

struct Friend {
    bool                state;
    QString             username;
    QString             name;
    QString             iconfile;
	std::vector<char>	icon;
};

struct Client {
        QString             username;
        QString             password;
        QString             iconfile;
        std::vector<char>	icon;
        std::vector<Friend>	friends;
};

namespace protocol {

class ClientSender : public QObject, public babel::protocol::Sender {
    Q_OBJECT
public:
	ClientSender(Client &client): _client{client} {}

	void receivePacket(babel::protocol::Packet &packet) override; /* done */
	void sendPacket(babel::protocol::Packet &packet) override; /* done */

    void setHost(QString const &host);
    void setPort(quint16 port);
    void setParent(QObject *parent);

    int run(void);

signals:
    void    disconnected(void);
    void    onPacketReceived(babel::protocol::Packet&);
    void    onFriendListChange(std::vector<Friend> const &friends);
    void    onCallRequest(QString username);

private:
	void parsPacketUpdateClient(babel::protocol::UpdateClient const &packet); /* done */
	void parsPacketUpdateFriendState(babel::protocol::UpdateFriendState const &packet);
	void parsPacketUpdateMessage(babel::protocol::UpdateMessage const &packet);
	void parsCliUpdateCall(babel::protocol::CliUpdateCall const &packet);

private:
    Client              &_client;
    QObject             *_parent;
    QString             _host;
    quint16             _port;
    nw::ATCPSocket      *_sock;
    std::unique_ptr<nw::Chopper>
                        _chop;
};

}

}
