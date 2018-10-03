/*
** EPITECH PROJECT, 2018
** babel
** File description:
** ServerProtocol.cpp
*/

#include <memory>
#include "ServerProtocol.hpp"
#include "CoreServer/CoreServer.hpp"
#include "Client/Client.hpp"
#include "Resources/Resources.hpp"

namespace srv {
namespace protocol {
	
void ServerSender::receivePacket(babel::protocol::Packet &packet)
{
	std::cerr << "Server: receive packet: "
		<< babel::protocol::Sender::humanReadable(packet.type)
		<< std::endl;
	switch (packet.type) {
		case babel::protocol::Packet::Type::Respond:
			parsPacketRespond(reinterpret_cast<babel::protocol::Respond &>(packet));
			break;
		case babel::protocol::Packet::Type::Connect:
			parsPacketConnect(reinterpret_cast<babel::protocol::Connect &>(packet));
			break;
		case babel::protocol::Packet::Type::GetMessages:
			break;
		case babel::protocol::Packet::Type::SendMessage:
			break;
		case babel::protocol::Packet::Type::UpdateLogo:
			break;
		case babel::protocol::Packet::Type::UpdateUser:
			break;
		case babel::protocol::Packet::Type::UpdateFriend:
			break;
		case babel::protocol::Packet::Type::UpdateClient:
			break;
		case babel::protocol::Packet::Type::UpdateMessage:
			break;
	}
}

void ServerSender::setSocket(nw::ATCPSocket *sock) {
	_sock = sock;

	nw::Chopper::Hooks	h;

	h.onCommandReceived = [this] (nw::Chopper::ByteArray &bytes) {
		this->receivePacket(
			*(reinterpret_cast<babel::protocol::Packet*>(
				bytes.buffer)));
	};
	_chop = std::make_unique<nw::Chopper>(*_sock, h);
}

void ServerSender::sendPacket(babel::protocol::Packet &packet)
{
	std::cerr << "Server : send packet ("
		<< packet.packetSize << ")" << std::endl;
	
	_chop->sendCommand(reinterpret_cast<std::uint8_t*>(&packet), packet.packetSize);
}

/* verif if username and password are correct */
void ServerSender::parsPacketConnect(babel::protocol::Connect const &packet)
{
	std::cerr << "receive connection" << std::endl;

	auto clients = server_g->db()["client"].getAll().where([&packet](db::Element const &e){
		return e["username"].as<std::string>() == packet.username
		&& e["password"].as<std::string>() == packet.password;
	});
	/* verif client isn't already connected */
	if (clients.size() == 0) {
		std::string	msg("Authentification failed, check your credentials.");
		auto *respond = new (msg.size()) babel::protocol::Respond;
		respond->type = babel::protocol::Packet::Type::Respond;
		respond->previous = babel::protocol::Packet::Type::Connect;
		respond->respond = babel::protocol::Respond::Type::KO;
		std::memmove(respond->data, msg.c_str(), msg.size());

		sendPacket(*respond);
		delete respond;
	} else {
		/* respond */
		auto *respond = new (sizeof(::protocol::data::ConnectReponse))
					babel::protocol::Respond;
		respond->type = babel::protocol::Packet::Type::Respond;
		respond->previous = babel::protocol::Packet::Type::Connect;
		respond->respond = babel::protocol::Respond::Type::OK;
		auto *data = reinterpret_cast<::protocol::data::ConnectReponse*>(respond->data);
		data->id = _uniqueId;
		data->udpRelayPort = server_g->getUdpRelayServer().getListenerPort();
		sendPacket(*respond);
		delete respond;

		/* client info */
		auto cli = Client::Info::deserializer(clients.back(), server_g->db());
		std::string icon;
		std::ifstream t(cli.iconfile);
		if (t.good()) {
			icon.assign((std::istreambuf_iterator<char>(t)), std::istreambuf_iterator<char>());
		}
		babel::protocol::UpdateClient *update = new (icon.size()) babel::protocol::UpdateClient;
		update->type = babel::protocol::Packet::Type::UpdateClient;
		std::strncpy(update->username, cli.username.c_str(), 128);
		update->size = icon.size();
		std::memcpy(update + 1, icon.c_str(), icon.size() + 1);
		sendPacket(*update);
		delete update;

		/* friends info */
		auto friendsRef = server_g->db()["friendListRef"].getAll().where([&clients](db::Element const &e) {
			return e["clientKey"].as<db::Key>() == clients.back()["primary_key"].as<db::Key>();
		});
		for (auto e : friendsRef) {
			Friend f = server_g->db()["friend"].get<Friend>(e["friendKey"].as<db::Key>());
			std::string icon;
			std::ifstream t(f.iconfile);
			if (t.good()) {
				icon.assign((std::istreambuf_iterator<char>(t)), std::istreambuf_iterator<char>());
			}
			auto *update = new (srv::Resources::basicLogoSize()) babel::protocol::UpdateFriendState;
			update->type = babel::protocol::Packet::Type::UpdateFriendState;
			std::strncpy(update->username, f.username.c_str(), 128);
			std::strncpy(update->name, f.name.c_str(), 128);
			update->state = f.state;
			std::memcpy(update->buffer, srv::Resources::basicLogo(), srv::Resources::basicLogoSize());
			sendPacket(*update);
			delete update;
		}
	}
}

} /* protocol */

} /* srv */