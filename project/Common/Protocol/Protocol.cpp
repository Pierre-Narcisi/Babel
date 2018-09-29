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

ClientSender	*clitmp = nullptr;
ServerSender	*servtmp = nullptr;

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


/* Client */

void ClientSender::receivePacket(Packet &packet)
{
	std::cerr << "Client : receive packet" << std::endl;
	switch (packet.type) {
		case Packet::Type::Respond:
			parsPacketRespond(reinterpret_cast<Respond &>(packet));
			break;
		case Packet::Type::UpdateClient:
			parsPacketUpdateClient(reinterpret_cast<UpdateClient &>(packet));
			break;
		case Packet::Type::UpdateFriendState:
			parsPacketUpdateFriendState(reinterpret_cast<UpdateFriendState &>(packet));
			break;
	}
}

void ClientSender::sendPacket(Packet &packet)
{
	if (servtmp) {
		servtmp->receivePacket(packet);
	}
}

void ClientSender::parsPacketUpdateClient(UpdateClient const &packet)
{
	_client.username = packet.username;
	char const *icon = reinterpret_cast<char const *>(&packet + 1);
	for (auto i = 0; i < packet.size; ++i)
		_client.icon.push_back(icon[i]);
}

void ClientSender::parsPacketUpdateFriendState(UpdateFriendState const &packet)
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


/* Server */
void ServerSender::receivePacket(Packet &packet)
{
	std::cerr << "Server : receive packet" << std::endl;
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

void ServerSender::sendPacket(Packet &packet)
{
	if (clitmp) {
		clitmp->receivePacket(packet);
	}
}

/* verif if username and password are correct */
void ServerSender::parsPacketConnect(Connect const &packet)
{
	std::cerr << "receive connection" << std::endl;

	Respond respond;
	respond.type = Packet::Type::Respond;
	respond.previous = Packet::Type::Connect;

	auto elems = _db["client"].getAll().where([&packet](db::Element const &e){
		return e["username"].as<std::string>() == packet.username
		&& e["password"].as<std::string>() == packet.password;
	});
	if (elems.size() == 0) {
		respond.respond = Respond::Type::KO;
		sendPacket(respond);
	} else {
		/* respond */
		respond.respond = Respond::Type::OK;
		sendPacket(respond);

		/* client info */
		Client cli = Client::deserializer(elems.back(), _db);
		std::string icon;
		std::ifstream t(cli.iconfile);
		if (t.good()) {
			icon.assign((std::istreambuf_iterator<char>(t)), std::istreambuf_iterator<char>());
		}
		UpdateClient *update = new UpdateClient [icon.size()];
		update->type = Packet::Type::UpdateClient;
		std::strncpy(update->username, cli.username.c_str(), 128);
		update->size = icon.size();
		std::memcpy(update + 1, icon.c_str(), icon.size() + 1);
		sendPacket(*update);
		delete update;

		/* friends info */
		auto friendsRef = _db["friendListRef"].getAll().where([&cli](db::Element const &e) {
			return e["clientKey"].as<db::Key>() == cli.key;
		});
		for (auto e : friendsRef) {
			Friend f = _db["friend"].get<Friend>(e["friendKey"].as<db::Key>());
			std::string icon;
			std::ifstream t(f.iconfile);
			if (t.good()) {
				icon.assign((std::istreambuf_iterator<char>(t)), std::istreambuf_iterator<char>());
			}
			UpdateFriendState *update = new UpdateFriendState[icon.size()];
			update->type = Packet::Type::UpdateFriendState;
			std::strncpy(update->username, f.username.c_str(), 128);
			std::strncpy(update->name, f.name.c_str(), 128);
			update->size = icon.size();
			update->state = f.state;
			std::memcpy(update + 1, icon.c_str(), icon.size() + 1);
			sendPacket(*update);
			delete update;
		}
	}
}

} /* protocol */

} /* babel */
