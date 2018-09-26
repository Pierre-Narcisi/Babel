/*
** EPITECH PROJECT, 2018
** babel
** File description:
** Protocol.h
*/

#pragma once

#include <string>

#include "Db.h"

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

struct getMessages : public Packet {
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
struct updateClient : public Packet {
	char		username[128];
	std::size_t	size;
	char		buffer[]; /* icon */
};

struct updateFriend : public Packet {
	bool		state;
	char		username[128];
	char		name[128];
	std::size_t	size;
	char		buffer[]; /* icon */
};

struct updateMessage : public Packet {
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
	Sender(db::Db *db): _db{db} {}

	void receivePacket(Packet &packet);

	void parsPacketRespond(Respond const &packet);
	void parsPacketConnect(Connect const &packet);

	/* tmp */
	void sendPacket(Packet &packet)
	{
		receivePacket(packet);
	}

private:
	db::Db		*_db;
};

} /* protocol */

} /* babel */
