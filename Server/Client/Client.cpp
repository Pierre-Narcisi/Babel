/*
** EPITECH PROJECT, 2018
** babel
** File description:
** Client.cpp
*/

#include <boost/filesystem.hpp>
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

bool Client::iconIsDepackaged(void)
{
	return _infos->icon.size() != 0;
}

void Client::depackageIcon(void)
{
	std::ifstream t(constant::ressourcesFolder + _infos->iconfile);
	if (t.good()) {
		_infos->icon.assign((std::istreambuf_iterator<char>(t)), std::istreambuf_iterator<char>());
	} else {
		for (auto i = 0; i < srv::Ressources::basicLogoSize(); ++i)
			_infos->icon.push_back(srv::Ressources::basicLogo()[i]);
	}
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
		case babel::protocol::Packet::Type::CallRequest:
			parsPacketCallRequest(reinterpret_cast<babel::protocol::CallRequest &>(packet));
			break;
		case babel::protocol::Packet::Type::CallRespond:
			parsPacketCallRespond(reinterpret_cast<babel::protocol::CallRespond &>(packet));
			break;
		case babel::protocol::Packet::Type::CallEnd:
			parsPacketCallEnd(reinterpret_cast<babel::protocol::CallEnd &>(packet));
			break;
		case babel::protocol::Packet::Type::GetClientIp:
			parsPacketGetClientIp(reinterpret_cast<babel::protocol::GetClientIp &>(packet));
			break;
		case babel::protocol::Packet::Type::UpdateLogo:
			parsPacketUpdateLogo(reinterpret_cast<babel::protocol::UpdateLogo &>(packet));
			break;
		case babel::protocol::Packet::Type::UpdateUser:
			parsPacketUpdateUser(reinterpret_cast<babel::protocol::UpdateUser &>(packet));
			break;
		case babel::protocol::Packet::Type::UpdateFriend:
			parsPacketUpdateFriend(reinterpret_cast<babel::protocol::UpdateFriend &>(packet));
			break;
		case babel::protocol::Packet::Type::UpdateClient:
			break;
		case babel::protocol::Packet::Type::UpdateMessage:
			break;
	}
}

void Client::setCallMap(Client *c1, Client *c2, SetMapType type) {
	if (type == SetMapType::ADD) {
		c1->getCallMap()[c2->getInfos().username] = c2;
		c2->getCallMap()[c1->getInfos().username] = c1;
	} else {
		auto it1 = c1->_callMap.find(c2->getInfos().username);
		auto it2 = c2->_callMap.find(c1->getInfos().username);

		if (it1 != c1->getCallMap().end()) {
			c1->getCallMap().erase(it1);
		}
		if (it2 != c2->getCallMap().end()) {
			c2->getCallMap().erase(it2);
		}
	}
}

void Client::sendPacket(babel::protocol::Packet &packet)
{
	std::cerr << "Server : send packet ("
		<< humanReadable(packet.type) << " -- len="
		<< packet.packetSize << ")" << std::endl;
	
	_chop->sendCommand(reinterpret_cast<std::uint8_t*>(&packet), packet.packetSize);
}

void Client::parsPacketGetClientIp(babel::protocol::GetClientIp const &packet) {
	if (server_g->isConnected(packet.username) == false) {
		std::string	msg("user not connected.");
		sendErrorRespond(packet.type, msg);
	} else {
		auto &clt = server_g->getClient(packet.username);
		if (clt.isFriend(_infos->username) == false) {
			sendErrorRespond(packet.type,
				"You are not in the friend list of "
				+ std::string(packet.username) + ".");
			return;
		}
		auto endpoint = clt.getSocket().getBoostSocket().remote_endpoint();
		auto respond = babel::protocol::Respond::create(sizeof(proto::data::GetClientIpRespond));
		respond->previous = packet.type;
		respond->respond = babel::protocol::Respond::Type::OK;
		
		auto data = reinterpret_cast<proto::data::GetClientIpRespond*>(respond->data);
		std::strcpy(data->username, packet.username);
		data->ip = endpoint.address().to_v4().to_uint();
		sendPacket(*respond);
	}
}

void Client::parsPacketCallRespond(babel::protocol::CallRespond &packet) {
	try {
		auto &to = server_g->getClient(packet.toUsername);

		auto respond = babel::protocol::Respond::create(0);
		respond->previous = packet.type;
		respond->respond = babel::protocol::Respond::Type::OK;

		sendPacket(*respond);

		if (packet.respond == babel::protocol::CallRespond::REJECT) {
			setCallMap(this, &to, SetMapType::REMOVE);
		}
		to.sendPacket(packet);
	} catch (...) {
		std::string	msg("user not connected.");
		sendErrorRespond(packet.type, msg);
	}
}

void Client::parsPacketCallRequest(babel::protocol::CallRequest &packet) {
	try {
		auto &to = server_g->getClient(packet.username);

		if (_callMap.find(packet.username) != _callMap.end()) {
			std::string	msg(
				std::string("An other session with ")
				+ packet.username + " is active.");
			sendErrorRespond(packet.type, msg);
			return;
		}
		auto respond = babel::protocol::Respond::create(0);
		respond->previous = packet.type;
		respond->respond = babel::protocol::Respond::Type::OK;

		sendPacket(*respond);
		std::strcpy(packet.username, _infos->username.c_str());
		to.sendPacket(packet);
		setCallMap(this, &to, SetMapType::ADD);
	} catch (...) {
		std::string	msg("user not connected.");
		sendErrorRespond(packet.type, msg);
	}
}

void Client::parsPacketCallEnd(babel::protocol::CallEnd &packet) {
	auto it = _callMap.find(packet.username);

	if (it == _callMap.end()) {
		std::string	msg(
				std::string("No active session with ")
				+ packet.username + " found.");
		sendErrorRespond(packet.type, msg);
	} else {
		try {
			auto &to = server_g->getClient(packet.username);

			auto respond = babel::protocol::Respond::create(0);
			respond->previous = packet.type;
			respond->respond = babel::protocol::Respond::Type::OK;

			sendPacket(*respond);
			
			setCallMap(this, &to, SetMapType::REMOVE);
			std::strcpy(packet.username, _infos->username.c_str());
			to.sendPacket(packet);
		} catch (...) {
			std::string	msg("user not connected.");
			sendErrorRespond(packet.type, msg);
		}
	}
}

/* verif if username and password are correct */
void Client::parsPacketConnect(babel::protocol::Connect const &packet)
{
	std::cerr << "receive connection" << std::endl;

	std::cerr << "username : " << packet.username << std::endl;
	if (packet.connectionType == babel::protocol::Connect::Type::CONNECT) {
		connectToAccount(packet);
	} else {
		createAccount(packet);
	}
}

void Client::parsPacketUpdateFriend(babel::protocol::UpdateFriend const &packet)
{
	if (server_g->db()["client"].getAll().where([&packet](db::Element const &e) {
		return e["username"].as<std::string>() == packet.username;
	}).size() == 0) {
		sendErrorRespond(packet.type, "error : username " + std::string(packet.username) + "doesn't not exist");
	} else {
		switch (packet.what) {
			case babel::protocol::UpdateFriend::What::NEW:
				newFriend(reinterpret_cast<babel::protocol::UpdateFriend const &>(packet));
				break;
			case babel::protocol::UpdateFriend::What::UPDATE:
				updateFriend(reinterpret_cast<babel::protocol::UpdateFriend const &>(packet));
				break;
			case babel::protocol::UpdateFriend::What::ERASE:
				eraseFriend(reinterpret_cast<babel::protocol::UpdateFriend const &>(packet));
				break;
		}
	}
	sendValidRespond(packet.type, "");
}

void	Client::parsPacketUpdateLogo(babel::protocol::UpdateLogo const &packet)
{
	if (::boost::filesystem::is_directory(constant::ressourcesFolder) == false) {
		sendErrorRespond(babel::protocol::Packet::Type::UpdateLogo, "error : fail to get icon, sorry.");
		return;
	}
	std::remove((constant::ressourcesFolder + _infos->username).c_str());
	std::string iconfile = constant::ressourcesFolder + _infos->username + packet.extend;
	std::ofstream myfile{iconfile};
	if (myfile.good()) {
		myfile.write(packet.buffer, packet.size);
		sendValidRespond(packet.type, "");
		_infos->iconfile = iconfile;
		depackageIcon();
		auto client = server_g->db()["client"].getAll().where([this](db::Element const &e){
			return e["username"].as<std::string>() == _infos->username;
		});
		server_g->db()["client"][client.back()["primary_key"].as<db::Key>()]["icon"] = _infos->iconfile;
		updateStateOfFriends(true, true);
	} else {
		sendErrorRespond(babel::protocol::Packet::Type::UpdateLogo, "error : fail to get icon, sorry.");
	}
}

void	Client::parsPacketUpdateUser(babel::protocol::UpdateUser const &packet)
{
	auto client = server_g->db()["client"].getAll().where([this, &packet](db::Element const &e){
		return e["username"].as<std::string>() == _infos->username
		&& e["password"].as<std::string>() == packet.password;
	});
	if (client.size() == 0) {
		sendErrorRespond(packet.type, "error : Wrong password.");
	} else {
		server_g->db()["client"][client.back()["primary_key"].as<db::Key>()]["password"] = packet.newpassword;
		sendValidRespond(packet.type, "password was successfuly changed.");
	}
}

void Client::newFriend(babel::protocol::UpdateFriend const &packet)
{
	if (packet.username == _infos->username) {
		sendErrorRespond(packet.type, "error : you can't invite yourself.");
		return;
	}
	if (isFriend(packet.username) == true) {
		sendErrorRespond(packet.type, "error : " + std::string(packet.username) + " is already your friend.");
		return;
	}
	auto me = server_g->db()["client"].getAll().where([this](db::Element const &e) {
		return e["username"].as<std::string>() == _infos->username;
	});
	auto you = server_g->db()["client"].getAll().where([&packet](db::Element const &e) {
		return e["username"].as<std::string>() == packet.username;
	});
	auto mf = you.back();
	Friend myfriend;
	myfriend.username = mf["username"].as<std::string>();
	myfriend.iconfile = mf["icon"].as<std::string>();
	myfriend.name = mf["username"].as<std::string>();
	auto yourKey = server_g->db().insert(myfriend);

	Friend reverseFriend;
	reverseFriend.username = _infos->username;
	reverseFriend.iconfile = _infos->iconfile;
	reverseFriend.name = _infos->username;
	auto myKey = server_g->db().insert(reverseFriend);

	server_g->db().insert(FriendRef{me.back()["primary_key"].as<db::Key>(), yourKey});
	server_g->db().insert(FriendRef{you.back()["primary_key"].as<db::Key>(), myKey});

	if (server_g->isConnected(myfriend.username)) {
		if (iconIsDepackaged())
			depackageIcon();
		server_g->getClient(myfriend.username).sendUpdateFriendState(*_infos, true, true);
	}
	Client::Info friendInfos;
	friendInfos.username = myfriend.username;
	std::ifstream t(constant::ressourcesFolder + myfriend.iconfile);
	if (t.good()) {
		friendInfos.icon.assign((std::istreambuf_iterator<char>(t)), std::istreambuf_iterator<char>());
	} else {
		for (auto i = 0; i < srv::Ressources::basicLogoSize(); ++i)
			friendInfos.icon.push_back(srv::Ressources::basicLogo()[i]);
	}
	sendUpdateFriendState(
		friendInfos,
		server_g->isConnected(friendInfos.username),
		true);
}

bool Client::isFriend(std::string const &name, db::Key *ref) {
	auto refFriend = server_g->db()["friendListRef"].getAll().where([this, &name] (db::Element const &e) {
		auto me = server_g->db()["client"][e["clientKey"].as<db::Key>()];
		auto youRef = server_g->db()["friend"][e["friendKey"].as<db::Key>()]["clientRef"].as<db::Key>();

		return me["username"].as<std::string>() == _infos->username
		&& server_g->db()["client"][youRef]["username"].as<std::string>() == name;
	});
	if (ref && refFriend.size())
		*ref = refFriend.back()["primary_key"].as<db::Key>();
	return (refFriend.size() != 0);
}

void Client::updateFriend(babel::protocol::UpdateFriend const &packet)
{
	db::Key refFriend;

	if (isFriend(packet.username, &refFriend)) {
		sendErrorRespond(packet.type, "error : " + std::string(packet.username) + " isn't in your friend list.");
	} else {
		server_g->db()["friend"][refFriend]["name"] = packet.name;
		sendValidRespond(packet.type, "");
		/* update status on client */
	}
}

void Client::eraseFriend(babel::protocol::UpdateFriend const &packet)
{
	db::Key refFriend;
	db::Key revRefFriend;

	if (server_g->areFriends(_infos->username, packet.username, &refFriend) == false
	|| server_g->areFriends(packet.username, _infos->username, &revRefFriend) == false) {
		sendErrorRespond(packet.type, "error : " + std::string(packet.username) + " isn't in your friend list.");
	} else {
		server_g->db()["friend"].remove(server_g->db()["friendListRef"][refFriend]["friendKey"].as<db::Key>());
		server_g->db()["friend"].remove(server_g->db()["friendListRef"][revRefFriend]["friendKey"].as<db::Key>());
		server_g->db()["friendListRef"].remove(refFriend);
		server_g->db()["friendListRef"].remove(revRefFriend);
		sendValidRespond(packet.type, "friend successfuly deleted.");
		/* update status on client */
		auto update = babel::protocol::UpdateFriendState::create(0);
		update->type = babel::protocol::Packet::Type::UpdateFriendState;
		update->erase = true;
		if (server_g->isConnected(packet.username)) {
			std::strncpy(update->username, _infos->username.c_str(), 128);
			server_g->getClient(packet.username).sendPacket(*update);
		}
		std::strncpy(update->username, packet.username, 128);
		sendPacket(*update);
	}
}

void	Client::connectToAccount(babel::protocol::Connect const &packet)
{
	
	auto clients = server_g->db()["client"].getAll().where([&packet](db::Element const &e){
		return e["username"].as<std::string>() == packet.username
		&& e["password"].as<std::string>() == packet.password;
	});
	if (clients.size() == 0) {
		sendErrorRespond(packet.type, "Authentification failed, check your credentials.");
	} else if (server_g->isConnected(clients.back()["username"].as<std::string>())) {
		sendErrorRespond(packet.type, "Authentification failed, You already connected.");
	} else {
		sendInfoToClient(clients.back());
		updateStateOfFriends(true);
	}
}

void Client::sendValidRespond(babel::protocol::Packet::Type type, std::string const &message)
{
		auto respond = babel::protocol::Respond::create(message.size()) ;

		respond->type = babel::protocol::Packet::Type::Respond;
		respond->previous = type;
		respond->respond = babel::protocol::Respond::Type::OK;
		std::memmove(respond->data, message.c_str(), message.size() + 1);

		sendPacket(*respond);
}

void Client::sendErrorRespond(
	babel::protocol::Packet::Type type,
	std::string const &errorMsg)
{
		auto respond = babel::protocol::Respond::create(errorMsg.size());
		respond->type = babel::protocol::Packet::Type::Respond;
		respond->previous = type;
		respond->respond = babel::protocol::Respond::Type::KO;
		std::memmove(respond->data, errorMsg.c_str(), errorMsg.size() + 1);

		std::cout << "errorMsg.size() " << errorMsg.size()  << " " << respond->packetSize << std::endl;
		sendPacket(*respond);
}

void	Client::createAccount(babel::protocol::Connect const &packet)
{
	auto clients = server_g->db()["client"].getAll().where([&packet](db::Element const &e){
		return e["username"].as<std::string>() == packet.username;
	});
	if (clients.size() != 0) {
		std::string	msg("Authentification failed, this username is already used.");
		auto respond = babel::protocol::Respond::create(msg.size());
		respond->type = babel::protocol::Packet::Type::Respond;
		respond->previous = babel::protocol::Packet::Type::Connect;
		respond->respond = babel::protocol::Respond::Type::KO;
		std::memmove(respond->data, msg.c_str(), msg.size() + 1);

		sendPacket(*respond);
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
	auto respond = babel::protocol::Respond::create(sizeof(proto::data::ConnectRespond));
	respond->type = babel::protocol::Packet::Type::Respond;
	respond->previous = babel::protocol::Packet::Type::Connect;
	respond->respond = babel::protocol::Respond::Type::OK;
	auto *data = reinterpret_cast<proto::data::ConnectRespond*>(respond->data);
	data->id = _uniqueId;
	sendPacket(*respond);

	/* client info */
	depackageIcon();
	auto update = babel::protocol::UpdateClient::create(_infos->icon.size());
	update->type = babel::protocol::Packet::Type::UpdateClient;
	std::strncpy(update->username, client["username"].as<std::string>().c_str(), 128);
	update->size = _infos->icon.size();
	std::memcpy(update.get() + 1, _infos->icon.data(), _infos->icon.size());
	sendPacket(*update);

	/* friends info */
	auto friendsRef = server_g->db()["friendListRef"].getAll().where([&client](db::Element const &e) {
		return e["clientKey"].as<db::Key>() == client["primary_key"].as<db::Key>();
	});
	for (auto e : friendsRef) {
		Friend f = server_g->db()["friend"].get<Friend>(e["friendKey"].as<db::Key>());
		std::vector<char> icon;
		std::ifstream t(constant::ressourcesFolder + f.iconfile);

		if (t.good()) {
			icon.assign((std::istreambuf_iterator<char>(t)), std::istreambuf_iterator<char>());
		} else {
			for (auto i = 0; i < srv::Ressources::basicLogoSize(); ++i)
				icon.push_back(srv::Ressources::basicLogo()[i]);
		}
		auto update = babel::protocol::UpdateFriendState::create(icon.size());
		update->type = babel::protocol::Packet::Type::UpdateFriendState;
		std::strncpy(update->username, f.username.c_str(), 128);
		std::strncpy(update->name, f.name.c_str(), 128);
		update->state = f.state;
		std::memcpy(update->buffer, icon.data(), icon.size());
		sendPacket(*update);
	}
}

void	Client::updateStateOfFriends(bool state, bool fullUpdate)
{
	auto friendsRef = server_g->db()["friendListRef"].getAll().where([this](db::Element const &e) {
		return server_g->db()["client"][e["clientKey"].as<db::Key>()]["username"].as<std::string>() == _infos->username;
	});
	for (auto e : friendsRef) {
		Friend f = server_g->db()["friend"].get<Friend>(e["friendKey"].as<db::Key>());
		if (server_g->isConnected(f.username)) {
			server_g->getClient(f.username).sendUpdateFriendState(*_infos, state, fullUpdate);
		}
	}
}

void Client::sendUpdateFriendState(Client::Info const &infos, bool state, bool updateAll)
{
	if (updateAll == true) {
		auto update = babel::protocol::UpdateFriendState::create(infos.icon.size());
		update->type = babel::protocol::Packet::Type::UpdateFriendState;
		std::strncpy(update->username, infos.username.c_str(), 128);
		std::strncpy(update->name, infos.username.c_str(), 128);
		std::memcpy(update.get() + 1, infos.icon.data(), infos.icon.size());
		update->state = state;
		sendPacket(*update);
	} else {
		auto update = babel::protocol::UpdateFriendState::create(0);
		update->type = babel::protocol::Packet::Type::UpdateFriendState;
		std::strncpy(update->username, infos.username.c_str(), 128);
		update->state = state;
		sendPacket(*update);
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
	Client::Info info;
	info.username = element["username"].as<std::string>();
	info.password = element["password"].as<std::string>();
	info.iconfile = element["icon"].as<std::string>();

	return info;
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
	Friend f;

	f.state = server_g->isConnected(client.username);
	f.username = client.username;
	f.name = element["name"].as<std::string>();
	f.iconfile = client.iconfile;
	return f;
}

void	FriendRef::serializer(FriendRef const &ref, db::Element &elem, db::Db &db)
{
	elem["clientKey"] = ref.clientKey;
	elem["friendKey"] = ref.friendKey;
}

}