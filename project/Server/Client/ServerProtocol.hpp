/*
** EPITECH PROJECT, 2018
** babel
** File description:
** ServerProtocol.hpp
*/

#pragma once

#include "Protocol/Protocol.h"
#include "Network/ISocket.hpp"

namespace srv {

namespace protocol {

class ServerSender : public babel::protocol::Sender {
public:
	void receivePacket(babel::protocol::Packet &packet) override; /* done */
	void sendPacket(babel::protocol::Packet &packet) override; /* done */
	void setSocket(nw::ATCPSocket *sock) { _sock = sock; }

private:
	void parsPacketConnect(babel::protocol::Connect const &packet);
	void parsPacketgetMessages(babel::protocol::GetMessages const &packet);
	void parsPacketUpdateLogo(babel::protocol::UpdateLogo const &packet);
	void parsPacketUpdateUser(babel::protocol::UpdateUser const &packet);
	void parsPacketUpdateFriend(babel::protocol::UpdateFriend const &packet);

	nw::ATCPSocket *_sock;
};


} /* proto */

} /* srv */