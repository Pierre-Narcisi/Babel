/*
** EPITECH PROJECT, 2018
** babel
** File description:
** Protocol.cpp
*/

#include <iostream>
#include <algorithm>
#include <cstring>

#include "Protocol.h"

namespace babel {

namespace protocol {

/* verif if respond is OK or KO to a previous packet sended */
void Sender::parsPacketRespond(Respond const &packet)
{
	std::cerr << "respond " << (packet.respond ? "OK" : "KO") << " to ";
	std::cerr << humanReadable(packet.previous);
	std::cerr << std::endl;
}

std::string Sender::humanReadable(Packet::Type packetType) {
	switch (packetType) {
		case Packet::Type::Respond:
			return "Respond";
		case Packet::Type::Connect:
			return "Connect";
		case Packet::Type::GetMessages:
			return "getMessages";
		case Packet::Type::SendMessage:
			return "SendMessage";
		case Packet::Type::CallRequest:
			return "CallRequest";
		case Packet::Type::CallRespond:
			return "CallRespond";
		case Packet::Type::UpdateLogo:
			return "UpdateLogo";
		case Packet::Type::UpdateUser:
			return "UpdateUser";
		case Packet::Type::UpdateFriend:
			return "UpdateFriend";
		case Packet::Type::UpdateClient:
			return "UpdateClient";
		case Packet::Type::UpdateMessage:
			return "UpdateMessage";
		case Packet::Type::UpdateFriendState:
			return "UpdateFriendState";
		default:
			return "Unknown";
	}
}

} /* protocol */

} /* babel */
