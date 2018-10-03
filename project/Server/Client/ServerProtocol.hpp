/*
** EPITECH PROJECT, 2018
** babel
** File description:
** ServerProtocol.hpp
*/

#pragma once

#include "Protocol/Protocol.h"
#include "Network/ISocket.hpp"
#include "Chopper/Chopper.hpp"
#include "Db/Db.h"

namespace srv {

namespace protocol {

class ServerSender : public babel::protocol::Sender {
public:
	ServerSender(): {}

private:
	void parsPacketConnect(babel::protocol::Connect const &packet); /* done */
	void parsPacketgetMessages(babel::protocol::GetMessages const &packet);
	void parsPacketUpdateLogo(babel::protocol::UpdateLogo const &packet);
	void parsPacketUpdateUser(babel::protocol::UpdateUser const &packet);
	void parsPacketUpdateFriend(babel::protocol::UpdateFriend const &packet);

	void connectToAccount(babel::protocol::Connect const &packet);
	void createAccount(babel::protocol::Connect const &packet);
	void sendInfoToClient(db::Element const &client);

	nw::ATCPSocket			*_sock;
};


} /* proto */

} /* srv */