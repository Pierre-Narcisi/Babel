/*
** EPITECH PROJECT, 2018
** babel
** File description:
** Client.cpp
*/

#include "CoreServer/CoreServer.hpp"
#include "Client.hpp"

namespace srv {

Client::Client(::boost::asio::io_service &ios):
_sock(std::make_unique<::nw::boost::TCPSocket>(ios)),
_infos(std::make_unique<Client::Info>())
{}

std::string const	&Client::getUsername(void) const
{
	return _infos->username;
}

void	Client::start(void)
{
	_sock->addHandlerOnReadable(::boost::bind(
		&Client::_onReadableHandler,
		this,
		::boost::placeholders::_1));
	getSocket().start();
}

int	Client::_onReadableHandler(std::size_t len)
{
	std::cout << len << std::endl;
	std::uint8_t buffer[len];
	_sock->receive(buffer, len);
	_sender.receivePacket(reinterpret_cast<babel::protocol::Packet &>(buffer));
	// std::cout << std::string((char*) buffer, len) << std::endl;
	return (0);
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