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
#include <sys/types.h>
#include <stdio.h>
#include <fstream> 
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

	auto		&getCallMap(void) { return _callMap; }
	const auto	&getCallMap(void) const { return _callMap; }

	void	start(void);

	inline void	setOnDisconnect(std::function<void(void)> &&hdl) { _sock->setOnDisconnect(hdl); }

	void receivePacket(babel::protocol::Packet &packet) override; /* done */
	void sendPacket(babel::protocol::Packet &packet) override; /* done */

	bool iconIsDepackaged(void);
	void depackageIcon(void);
	// void sendUpdateFriendState(std::string const &username, std::string const &icon, bool state);
	void sendUpdateFriendState(Client::Info const &infos, bool state, bool updateAll = false);
	void updateStateOfFriends(bool state);

private:
	explicit Client(::boost::asio::io_service &ios);

	void parsPacketConnect(babel::protocol::Connect const &packet); /* done */
	void parsPacketCallRequest(babel::protocol::CallRequest &packet);
	void parsPacketCallRespond(babel::protocol::CallRespond &packet);
	void parsPacketCallEnd(babel::protocol::CallEnd &packet);
	void parsPacketGetClientIp(babel::protocol::GetClientIp const &packet);
	void parsPacketgetMessages(babel::protocol::GetMessages const &packet);
	void parsPacketUpdateLogo(babel::protocol::UpdateLogo const &packet);
	void parsPacketUpdateUser(babel::protocol::UpdateUser const &packet);
	void parsPacketUpdateFriend(babel::protocol::UpdateFriend const &packet);

	enum class SetMapType : bool { ADD = true, REMOVE = false};
	static void setCallMap(Client *c1, Client *c2, SetMapType type);
	bool	isFriend(std::string const &name, db::Key *ref = nullptr);

	void sendErrorRespond(
		babel::protocol::Packet::Type type,
		std::string const &errorMessage);
	void connectToAccount(babel::protocol::Connect const &packet);
	void createAccount(babel::protocol::Connect const &packet);
	void sendInfoToClient(db::Element const &client);
	void newFriend(babel::protocol::UpdateFriend const &packet);
	void updateFriend(babel::protocol::UpdateFriend const &packet);
	void eraseFriend(babel::protocol::UpdateFriend const &packet);

	int		_onReadableHandler(std::size_t len);
	db::Key		newFriend(std::string const &friendName, db::Db &db);

	std::unique_ptr<nw::ATCPSocket>	_sock;
	std::unique_ptr<nw::Chopper>	_chop;
	std::uintptr_t			_uniqueId;
	std::unique_ptr<Info>		_infos;
	std::unordered_map<std::string, Client*>
					_callMap;
};

struct Client::Info {
	std::string			username;
	std::string			password;
	std::string			iconfile;
	std::string			icon;

	static void		serializer(Client::Info const &client, db::Element &element, db::Db &db);
	static Client::Info	deserializer(db::Element &element, db::Db &db);
};

struct Friend {
	bool				state;
	std::string			username;
	std::string			name;
	std::string			iconfile;
	std::string	icon;

	static void	serializer(Friend const &myfriend, db::Element &element, db::Db &db);
	static Friend	deserializer(db::Element &element, db::Db &db);
};

struct FriendRef {
	db::Key clientKey;
	db::Key friendKey;

	static void	serializer(FriendRef const &pair, db::Element &elem, db::Db &db);
};

}