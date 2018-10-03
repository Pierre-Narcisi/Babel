/*
** EPITECH PROJECT, 2018
** babel
** File description:
** Client.cpp
*/

#include "CoreServer/CoreServer.hpp"
#include "Constant.hpp"
#include "Resources/Resources.hpp"
#include "Client.hpp"

namespace srv {

Client::Client(::boost::asio::io_service &ios):
_sock(std::make_unique<::nw::boost::TCPSocket>(ios)),
_uniqueId(reinterpret_cast<std::uintptr_t>(this)),
_infos(std::make_unique<Client::Info>())
{
	nw::Chopper::Hooks	h;

	h.onCommandReceived = [this] (nw::Chopper::ByteArray &bytes) {
		this->receivePacket(
			*(reinterpret_cast<babel::protocol::Packet*>(
				bytes.buffer)));
	};
	_chop = std::make_unique<nw::Chopper>(*_sock, h);

}

std::string const	&Client::getUsername(void) const
{
	return _infos->username;
}

void	Client::start(void)
{
	// _sock->addHandlerOnReadable(::boost::bind(
	// 	&Client::_onReadableHandler,
	// 	this,
	// 	::boost::placeholders::_1));
	getSocket().start();
}

int	Client::_onReadableHandler(std::size_t len)
{
	// std::cout << len << std::endl;
	// std::uint8_t buffer[len];
	// _sock->receive(buffer, len);
	// _sender.receivePacket(reinterpret_cast<babel::protocol::Packet &>(buffer));
	// // std::cout << std::string((char*) buffer, len) << std::endl;
	return (0);
}

void Client::receivePacket(babel::protocol::Packet &packet)
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

void Client::sendPacket(babel::protocol::Packet &packet)
{
	std::cerr << "Server : send packet ("
		<< packet.packetSize << ")" << std::endl;
	
	_chop->sendCommand(reinterpret_cast<std::uint8_t*>(&packet), packet.packetSize);
}

/* verif if username and password are correct */
void Client::parsPacketConnect(babel::protocol::Connect const &packet)
{
	std::cerr << "receive connection" << std::endl;

	std::cout << "type : " << packet.connectionType << std::endl;
	std::cout << "username : " << packet.username << std::endl;
	std::cout << "password : " << packet.password << std::endl;
	if (packet.connectionType == babel::protocol::Connect::Type::CONNECT) {
		connectToAccount(packet);
	} else {
		createAccount(packet);
	}
}

void parsPacketUpdateFriend(babel::protocol::UpdateFriend const &packet)
{
	switch (packet.what) {
		case babel::protocol::UpdateFriend::What::NEW:
			break;
		case babel::protocol::UpdateFriend::What::ERASE:
			break;
		case babel::protocol::UpdateFriend::What::UPDATE:
			break;
	}
}

void	Client::connectToAccount(babel::protocol::Connect const &packet)
{
	auto clients = server_g->db()["client"].getAll().where([&packet](db::Element const &e){
		return e["username"].as<std::string>() == packet.username
		&& e["password"].as<std::string>() == packet.password;
	});
	/* verif client isn't already connected */
	if (clients.size() == 0) {
		sendErrorRespond("Authentification failed, check your credentials.");
	} else if (server_g->isConnected(clients.back()["username"].as<std::string>())) {
		sendErrorRespond("Authentification failed, You already connected.");
	} else {
		sendInfoToClient(clients.back());
	}
}

void Client::sendErrorRespond(std::string const &errorMsg)
{
		auto *respond = new (errorMsg.size()) babel::protocol::Respond;
		respond->type = babel::protocol::Packet::Type::Respond;
		respond->previous = babel::protocol::Packet::Type::Connect;
		respond->respond = babel::protocol::Respond::Type::KO;
		std::memmove(respond->data, errorMsg.c_str(), errorMsg.size());

		sendPacket(*respond);
		delete respond;
}
void	Client::createAccount(babel::protocol::Connect const &packet)
{
	auto clients = server_g->db()["client"].getAll().where([&packet](db::Element const &e){
		return e["username"].as<std::string>() == packet.username;
	});
	if (clients.size() != 0) {
		std::string	msg("Authentification failed, this username is already used.");
		auto *respond = new (msg.size()) babel::protocol::Respond;
		respond->type = babel::protocol::Packet::Type::Respond;
		respond->previous = babel::protocol::Packet::Type::Connect;
		respond->respond = babel::protocol::Respond::Type::KO;
		std::memmove(respond->data, msg.c_str(), msg.size());

		sendPacket(*respond);
		delete respond;
	} else {
		Client::Info client;

		client.username = packet.username;
		client.password = packet.password;
		client.iconfile = constant::defUserFileIcon;

		auto idClient = server_g->db().insert(client);
		sendInfoToClient(server_g->db()["client"][idClient]);
	}
}

void Client::sendInfoToClient(db::Element const &client)
{
	_infos->username = client["username"].as<std::string>();
	_infos->iconfile = client["icon"].as<std::string>();
	// attendre la connection udp du client
	/* respond */
	auto *respond = new (sizeof(::protocol::data::ConnectReponse))
				babel::protocol::Respond;
	respond->type = babel::protocol::Packet::Type::Respond;
	respond->previous = babel::protocol::Packet::Type::Connect;
	respond->respond = babel::protocol::Respond::Type::OK;
	auto *data = reinterpret_cast<::protocol::data::ConnectReponse*>(respond->data);
	data->id = _uniqueId;
	sendPacket(*respond);
	delete respond;

	/* client info */
	std::string icon;
	std::ifstream t(client["icon"].as<std::string>());
	if (t.good()) {
		icon.assign((std::istreambuf_iterator<char>(t)), std::istreambuf_iterator<char>());
	}
	babel::protocol::UpdateClient *update = new (icon.size()) babel::protocol::UpdateClient;
	update->type = babel::protocol::Packet::Type::UpdateClient;
	std::strncpy(update->username, client["username"].as<std::string>().c_str(), 128);
	update->size = icon.size();
	std::memcpy(update + 1, icon.c_str(), icon.size() + 1);
	sendPacket(*update);
	delete update;

	/* friends info */
	auto friendsRef = server_g->db()["friendListRef"].getAll().where([&client](db::Element const &e) {
		return e["clientKey"].as<db::Key>() == client["primary_key"].as<db::Key>();
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

db::Key	Client::newFriend(std::string const &friendName, db::Db &db)
{
	auto me = db["client"].getAll().where([this](db::Element const &e){
		return e["username"].as<std::string>() == _infos->username;
	});
	auto you = db["client"].getAll().where([&friendName](db::Element const &e){
		return e["username"].as<std::string>() == friendName;
	});
	auto mf = you.back();
	Friend myfriend;
	myfriend.username = mf["username"].as<std::string>();
	myfriend.iconfile = mf["icon"].as<std::string>();
	myfriend.name = mf["username"].as<std::string>();
	auto yourKey = db.insert(myfriend);

	Friend reverseFriend;
	myfriend.username = _infos->username;
	myfriend.iconfile = _infos->iconfile;
	myfriend.name = _infos->username;
	auto myKey = db.insert(myfriend);

	db.insert(FriendRef{me.back()["primary_key"].as<db::Key>(), yourKey});
	db.insert(FriendRef{you.back()["primary_key"].as<db::Key>(), myKey});
	return yourKey;
}

void	Client::Info::serializer(Client::Info const &client, db::Element &element, db::Db &db)
{
	element["username"] = client.username;
	element["password"] = client.password;
	element["icon"] = client.iconfile;
}

Client::Info	Client::Info::deserializer(db::Element &element, db::Db &db)
{
	return Client::Info{
		.username = element["username"].as<std::string>(),
		.password = element["password"].as<std::string>(),
		.iconfile = element["icon"].as<std::string>()
	};
}

void	Friend::serializer(Friend const &myfriend, db::Element &element, db::Db &db)
{
	auto elems = db["client"].getAll().where([&myfriend] (db::Element const &e) {
		return e["username"].as<std::string>() == myfriend.username;
	});
	if (elems.size() == 0)
		return;
	element["clientRef"] = elems.back()["primary_key"];
	element["name"] = myfriend.name;
}

Friend	Friend::deserializer(db::Element &element, db::Db &db)
{
	auto client = db["client"].get<Client::Info>(element["clientRef"].as<db::Key>());
	return Friend{
		.state = server_g->isConnected(client.username),
		.username = client.username,
		.name = element["name"].as<std::string>(),
		.iconfile = client.iconfile
	};
}

void	FriendRef::serializer(FriendRef const &ref, db::Element &elem, db::Db &db)
{
	elem["clientKey"] = ref.clientKey;
	elem["friendKey"] = ref.friendKey;
}

}