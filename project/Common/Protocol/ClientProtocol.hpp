/*
** EPITECH PROJECT, 2018
** babel
** File description:
** ClientProtocol.hpp
*/

#pragma once

#include <string>
#include <vector>

#include "Protocol/Protocol.h"

namespace client {

struct Client {
	std::string		username;
	std::string		password;
	std::string		iconfile;
	std::vector<char>	icon;
	std::vector<Friend>	friends;
};

struct Friend {
	bool			state;
	std::string		username;
	std::string		name;
	std::string		iconfile;
	std::vector<char>	icon;
};

namespace protocol {

class ClientSender : public babel::protocol::Sender {
public:
	ClientSender(Client &client): _client{client} {}

	void receivePacket(babel::protocol::Packet &packet) override; /* done */
	void sendPacket(babel::protocol::Packet &packet) override; /* done */

private:
	void parsPacketUpdateClient(babel::protocol::UpdateClient const &packet); /* done */
	void parsPacketUpdateFriendState(babel::protocol::UpdateFriendState const &packet);
	void parsPacketUpdateMessage(babel::protocol::UpdateMessage const &packet);
	void parsCliUpdateCall(babel::protocol::CliUpdateCall const &packet);

private:
	Client		&_client;
};

}

}