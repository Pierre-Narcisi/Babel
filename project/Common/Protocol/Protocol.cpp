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
	switch (packet.previous) {
		case Packet::Type::Respond:
			std::cerr << "Respond";break;
		case Packet::Type::Connect:
			std::cerr << "Connect";break;
        case Packet::Type::GetMessages:
			std::cerr << "getMessages";break;
		case Packet::Type::SendMessage:
			std::cerr << "Send";break;
		case Packet::Type::UpdateLogo:
			std::cerr << "UpdateLogo";break;
		case Packet::Type::UpdateUser:
			std::cerr << "UpdateUser";break;
		case Packet::Type::UpdateFriend:
			std::cerr << "UpdateFriend";break;
		case Packet::Type::UpdateClient:
			std::cerr << "UpdateClient";break;
		case Packet::Type::UpdateMessage:
			std::cerr << "UpdateMessage";break;
        default: break;
	}
	std::cerr << std::endl;
}

} /* protocol */

} /* babel */
