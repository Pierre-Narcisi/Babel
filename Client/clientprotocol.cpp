/*
** EPITECH PROJECT, 2018
** babel
** File description:
** ClientProtocol.cpp
*/

#include <iostream>
#include <functional>
#include <QFile>
#include <memory>
#include "clientprotocol.h"

namespace client {

namespace protocol {

int ClientSender::run(void) {
    try {
        _sock = new nw::qt::TCPSocket(_parent);
        nw::Chopper::Hooks	h;
        h.onCommandReceived = [this] (nw::Chopper::ByteArray &bytes) {
            auto *p = reinterpret_cast<babel::protocol::Packet*>(bytes.buffer);
            std::cout << "Packet Size = " << p->packetSize << std::endl;
            this->receivePacket(*p);
            emit onPacketReceived(*p);
        };
        _chop = std::unique_ptr<nw::Chopper>(new nw::Chopper(*_sock, h));

        _sock->connect(_host.toStdString(), _port);
        _sock->setOnDisconnect([this] {
            emit disconnected();
        });
        return (0);
    } catch (...) {
        return (-1);
    }
}

void ClientSender::end(void) {
    _client.friends.clear();
    delete _sock;
}

void ClientSender::setHost(const QString &host) {
    _host = host;
}

void ClientSender::setPort(quint16 port) {
    _port = port;
}

void ClientSender::setParent(QObject *parent) {
    _parent = parent;
}

void ClientSender::receivePacket(babel::protocol::Packet &packet)
{
    std::cerr << "Client : receive packet ("
              << humanReadable(packet.type) << ")" << std::endl;
	switch (packet.type) {
		case babel::protocol::Packet::Type::Respond:
			parsPacketRespond(reinterpret_cast<babel::protocol::Respond &>(packet));
			break;
		case babel::protocol::Packet::Type::UpdateClient:
			parsPacketUpdateClient(reinterpret_cast<babel::protocol::UpdateClient &>(packet));
			break;
		case babel::protocol::Packet::Type::UpdateFriendState:
			parsPacketUpdateFriendState(reinterpret_cast<babel::protocol::UpdateFriendState &>(packet));
			break;
        case babel::protocol::Packet::Type::CallRequest:
            emit onCallRequest(reinterpret_cast<babel::protocol::CallRequest&>(packet).username);
            break;
        case babel::protocol::Packet::Type::CallEnd:
            emit onCallEnd(reinterpret_cast<babel::protocol::CallEnd&>(packet).username);
            break;
        default: break;
	}
}

void ClientSender::sendPacket(babel::protocol::Packet &packet)
{
    _chop->sendCommand(reinterpret_cast<std::uint8_t*>(&packet), packet.packetSize);
}

void ClientSender::parsPacketUpdateClient(babel::protocol::UpdateClient const &packet)
{
	_client.username = packet.username;
	char const *icon = reinterpret_cast<char const *>(&packet + 1);
        for (std::size_t i = 0; i < packet.size; ++i)
		_client.icon.push_back(icon[i]);
}

void ClientSender::parsPacketUpdateFriendState(babel::protocol::UpdateFriendState const &packet)
{
	auto f = std::find_if(_client.friends.begin(), _client.friends.end(), [&packet](Friend const &e) {
		return packet.username == e.username;
	});
	if (f != _client.friends.end()) {
        if (packet.erase == false) {
            f->state = packet.state;
            f->username = packet.username;
            if (packet.size != 0) {
                char const *icon = reinterpret_cast<char const *>(&packet + 1);
                for (std::size_t i = 0; i < packet.size; ++i)
                    f->icon.push_back(icon[i]);
            }
        } else {
            _client.friends.erase(f);
        }
	} else {
		_client.friends.push_back(Friend{
			.state = packet.state,
			.username = packet.username,
			.name = packet.name
		});
		if (packet.size != 0) {
			char const *icon = reinterpret_cast<char const *>(&packet + 1);

            _client.friends.back().icon.reserve(packet.size);
            for (std::size_t i = 0; i < packet.size; ++i)
				_client.friends.back().icon.push_back(icon[i]);
		}
	}
    emit onFriendListChange(_client.friends);
}

}

}
