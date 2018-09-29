/*
** EPITECH PROJECT, 2018
** babel
** File description:
** ClientProtocol.cpp
*/

#include <iostream>
#include <functional>

#include "ClientProtocol.hpp"

namespace client {

namespace protocol {

void ClientSender::receivePacket(babel::protocol::Packet &packet)
{
	std::cerr << "Client : receive packet" << std::endl;
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
	}
}

void ClientSender::sendPacket(babel::protocol::Packet &packet)
{
	/* send the packet */
}

void ClientSender::parsPacketUpdateClient(babel::protocol::UpdateClient const &packet)
{
	_client.username = packet.username;
	char const *icon = reinterpret_cast<char const *>(&packet + 1);
	for (auto i = 0; i < packet.size; ++i)
		_client.icon.push_back(icon[i]);
}

void ClientSender::parsPacketUpdateFriendState(babel::protocol::UpdateFriendState const &packet)
{
	auto f = std::find_if(_client.friends.begin(), _client.friends.end(), [&packet](Friend const &e) {
		return packet.username == e.username;
	});
	if (f != _client.friends.end()) {
		f->state = packet.state;
		f->username = packet.username;
		f->name = packet.name;
		if (packet.size != 0) {
			char const *icon = reinterpret_cast<char const *>(&packet + 1);
			for (auto i = 0; i < packet.size; ++i)
				f->icon.push_back(icon[i]);
		}
	} else {
		_client.friends.push_back(Friend{
			.state = packet.state,
			.username = packet.username,
			.name = packet.name
		});
		if (packet.size != 0) {
			char const *icon = reinterpret_cast<char const *>(&packet + 1);
			for (auto i = 0; i < packet.size; ++i)
				_client.friends.back().icon.push_back(icon[i]);
		}
	}
}

}

}
