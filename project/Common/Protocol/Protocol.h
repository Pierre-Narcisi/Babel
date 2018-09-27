/*
** EPITECH PROJECT, 2018
** babel
** File description:
** Protocol.h
*/

#pragma once

#include <string>

#include "BabelStruct.h"

namespace babel {

namespace protocol {

/* Common */

struct Packet {
	enum class Type {
		Respond,
		Connect,
		getMessages,
		Send,
		UpdateLogo,
		UpdateUser,
		UpdateFriend,
		UpdateClient,
		UpdateMessage
	} type;
};

struct Respond : public Packet {
	enum Type : bool {OK = true, KO = false};
	Packet::Type	previous;
	Respond::Type	respond;
};

/* Client -> Server */
struct Connect : public Packet {
	char		username[128];
	char		password[128];
};

struct GetMessages : public Packet {
	char		username[128];
	std::size_t	start;
	std::size_t	number;
};

struct UpdateLogo : public Packet {
	std::size_t	size;
	char		buffer[];
};
struct UpdateUser : public Packet {
	char		username[128];
	char		password[128];
};
struct UpdateFriend : public Packet {
	enum class What {Update, Erase};
	What		what;
	char		username[128];
	char		name[128];
};

struct Send : public Packet {
	char		username[128];
	std::size_t	size;
	char		buffer[]; /* message */
};

/* Server -> Client */
struct UpdateClient : public Packet {
	char		username[128];
	std::size_t	size;
	char		buffer[]; /* icon */
};

struct UpdateFriends : public Packet {
	bool		state;
	char		username[128];
	char		name[128];
	std::size_t	size;
	char		buffer[]; /* icon */
};

struct UpdateMessage : public Packet {
	struct Message {
		std::size_t	size;
		char		buffer[];
	};
	char		username[128];
	std::size_t	nbMessage;
	Message		messages[];
};

class Sender {
public:
	virtual void receivePacket(Packet &packet) = 0;
	virtual void sendPacket(Packet &packet) = 0;

protected:
	void parsPacketRespond(Respond const &packet);
};

class ClientSender : public Sender {
public:
	ClientSender(Client &client): _client{client} {}

	void receivePacket(Packet &packet) override;
	void sendPacket(Packet &packet) override;

private:
	void parsPacketUpdateClient(UpdateClient const &packet);
	void parsPacketUpdateFriend(UpdateFriend const &packet);
	void parsPacketUpdateMessage(UpdateMessage const &packet);

private:
	Client &_client;
};

class ServerSender : public Sender {
public:
	ServerSender(db::Db &db): _db{db} {}

	void receivePacket(Packet &packet) override;
	void sendPacket(Packet &packet) override;

private:
	void parsPacketConnect(Connect const &packet);
	void parsPacketgetMessages(GetMessages const &packet);
	void parsPacketUpdateLogo(UpdateLogo const &packet);
	void parsPacketUpdateUser(UpdateUser const &packet);
	void parsPacketUpdateFriend(UpdateFriend const &packet);

private:
	db::Db		&_db;
};

extern ClientSender	*clitmp;
extern ServerSender	*servtmp;

} /* protocol */

} /* babel */
