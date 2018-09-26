/*
** EPITECH PROJECT, 2018
** babel
** File description:
** Protocol.cpp
*/

#include <iostream>
#include <algorithm>

#include "Protocol.h"

namespace babel {

namespace protocol {

void Sender::receivePacket(Packet &packet)
{
	std::cerr << "receive packet" << std::endl;
	switch (packet.type) {
		case Packet::Type::Respond:
			parsPacketRespond(reinterpret_cast<Respond &>(packet));
			break;
		case Packet::Type::Connect:
			parsPacketConnect(reinterpret_cast<Connect &>(packet));
			break;
		case Packet::Type::getMessages:
			break;
		case Packet::Type::Send:
			break;
		case Packet::Type::UpdateLogo:
			break;
		case Packet::Type::UpdateUser:
			break;
		case Packet::Type::UpdateFriend:
			break;
		case Packet::Type::UpdateClient:
			break;
		case Packet::Type::UpdateMessage:
			break;

	}
}

/* verif if respond is OK or KO to a previous packet sended */
void Sender::parsPacketRespond(Respond const &packet)
{
	std::cerr << "respond " << (packet.respond ? "OK" : "KO") << " to ";
	switch (packet.previous) {
		case Packet::Type::Respond:
			std::cerr << "Respond";break;
		case Packet::Type::Connect:
			std::cerr << "Connect";break;
		case Packet::Type::getMessages:
			std::cerr << "getMessages";break;
		case Packet::Type::Send:
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
	}
	std::cerr << std::endl;
}

/* verif if username and password are correct */
void Sender::parsPacketConnect(Connect const &packet)
{
	std::cerr << "receive connection" << std::endl;
	if (_db == nullptr)
		return;

	Respond respond;
	respond.type = Packet::Type::Respond;
	respond.previous = Packet::Type::Connect;

	auto elems = (*_db)["client"].getAll().where([&packet](db::Element const &e){
		return e["username"].as<std::string>() == packet.username
		&& e["password"].as<std::string>() == packet.password;
	});
	if (elems.size() != 0) {
		respond.respond = Respond::Type::OK;
		sendPacket(respond);
	} else {
		respond.respond = Respond::Type::KO;
		sendPacket(respond);
	}
}

}

}
