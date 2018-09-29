/*
** EPITECH PROJECT, 2018
** babel
** File description:
** ServerProtocol.hpp
*/

#pragma once

#include "Protocol/Protocol.h"

namespace srv {

namespace protocol {

class ServerSender : public babel::protocol::Sender {
public:
	void receivePacket(babel::protocol::Packet &packet) override; /* done */
	void sendPacket(babel::protocol::Packet &packet) override; /* done */

private:
	void parsPacketConnect(babel::protocol::Connect const &packet);
	void parsPacketgetMessages(babel::protocol::GetMessages const &packet);
	void parsPacketUpdateLogo(babel::protocol::UpdateLogo const &packet);
	void parsPacketUpdateUser(babel::protocol::UpdateUser const &packet);
	void parsPacketUpdateFriend(babel::protocol::UpdateFriend const &packet);
};


} /* proto */

} /* srv */