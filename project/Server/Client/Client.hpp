/*
** EPITECH PROJECT, 2018
** babel
** File description:
** Client.hpp
*/

#pragma once

#include <boost/enable_shared_from_this.hpp>
#include <boost/shared_ptr.hpp>
#include "Network/BoostSocket.hpp"
#include "Chopper/Chopper.hpp"
#include "Protocol/Protocol.h"
#include "Db/Db.h"

#include <iostream>

namespace srv {

class CoreServer;

class Client: public ::boost::enable_shared_from_this<Client>, public babel::protocol::Sender {
public:
	using ptr = ::boost::shared_ptr<Client>;
	struct Info;

	static inline ptr	create(::boost::asio::io_service& ios) {
		return ptr(new Client(ios));
	}

	inline nw::boost::TCPSocket	&getSocket(void) { return reinterpret_cast<::nw::boost::TCPSocket&>(*_sock); }
	std::string const		&getUsername(void) const;
	inline Client::Info		&getInfos(void) {return *_infos; }

	void	start(void);

	inline void	setOnDisconnect(std::function<void(void)> &&hdl) { _sock->setOnDisconnect(hdl); }

	void receivePacket(babel::protocol::Packet &packet) override; /* done */
	void sendPacket(babel::protocol::Packet &packet) override; /* done */

private:
	explicit Client(::boost::asio::io_service &ios);

	void parsPacketConnect(babel::protocol::Connect const &packet); /* done */
	void parsPacketgetMessages(babel::protocol::GetMessages const &packet);
	void parsPacketUpdateLogo(babel::protocol::UpdateLogo const &packet);
	void parsPacketUpdateUser(babel::protocol::UpdateUser const &packet);
	void parsPacketUpdateFriend(babel::protocol::UpdateFriend const &packet);

	void sendErrorRespond(std::string const &errorMessage);
	void connectToAccount(babel::protocol::Connect const &packet);
	void createAccount(babel::protocol::Connect const &packet);
	void sendInfoToClient(db::Element const &client);

	int		_onReadableHandler(std::size_t len);
	db::Key		newFriend(std::string const &friendName, db::Db &db);

	std::unique_ptr<nw::ATCPSocket>	_sock; /* use abstract class instead ? */
	std::unique_ptr<nw::Chopper>	_chop;
	std::uintptr_t			_uniqueId;
	std::unique_ptr<Info>		_infos;
};

struct Client::Info {
	std::string			username;
	std::string			password;
	std::string			iconfile;
	std::vector<std::int8_t>	icon;

	static void		serializer(Client::Info const &client, db::Element &element, db::Db &db);
	static Client::Info	deserializer(db::Element &element, db::Db &db);
};

struct Friend {
	bool				state;
	std::string			username;
	std::string			name;
	std::string			iconfile;
	std::vector<std::int8_t>	icon;

	static void	serializer(Friend const &myfriend, db::Element &element, db::Db &db);
	static Friend	deserializer(db::Element &element, db::Db &db);
};

struct FriendRef {
	db::Key clientKey;
	db::Key friendKey;

	static void	serializer(FriendRef const &pair, db::Element &elem, db::Db &db);
};

}