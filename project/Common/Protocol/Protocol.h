/*
** EPITECH PROJECT, 2018
** babel
** File description:
** Protocol.h
*/

#pragma once

#include <string>

#include "Db/Db.h"

namespace srv {
	class Client;
}

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
		UpdateFriendState,
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

	void *operator new[](std::size_t s)
	{
		return ::operator new(sizeof(UpdateLogo) + s + 1);
	}

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

struct SendMessage : public Packet {
	char		username[128];
	std::size_t	size;
	char		buffer[]; /* message */

	void *operator new[](std::size_t s)
	{
		return ::operator new(sizeof(SendMessage) + s + 1);
	}

};

/* Server -> Client */
struct UpdateClient : public Packet {
	char		username[128];
	std::size_t	size;
	char		buffer[]; /* icon */

	static void *operator new[](std::size_t s)
	{
		return ::operator new(sizeof(UpdateClient) + s + 1);
	}
};

struct UpdateFriendState : public Packet {
	bool		state;
	char		username[128];
	char		name[128];
	std::size_t	size;
	char		buffer[]; /* icon */

	void *operator new[](std::size_t s)
	{
		return ::operator new(sizeof(UpdateFriendState) + s + 1);
	}
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

struct CliUpdateCall : public Packet {

};

struct ServUpdateCall : public Packet {
	
};

class Sender {
public:
	virtual void receivePacket(Packet &packet) = 0;
	virtual void sendPacket(Packet &packet) = 0;

protected:
	void parsPacketRespond(Respond const &packet); /* done */
};

class ClientSender : public Sender {
public:
	// ClientSender(Client &client): _client{client} {}

	void receivePacket(Packet &packet) override; /* done */
	void sendPacket(Packet &packet) override; /* done */

private:
	void parsPacketUpdateClient(UpdateClient const &packet); /* done */
	void parsPacketUpdateFriendState(UpdateFriendState const &packet);
	void parsPacketUpdateMessage(UpdateMessage const &packet);
	void parsCliUpdateCall(CliUpdateCall const &packet);

private:
	// Client		&_client;
};

class ServerSender : public Sender {
public:
	void receivePacket(Packet &packet) override; /* done */
	void sendPacket(Packet &packet) override; /* done */

private:
	void parsPacketConnect(Connect const &packet);
	void parsPacketgetMessages(GetMessages const &packet);
	void parsPacketUpdateLogo(UpdateLogo const &packet);
	void parsPacketUpdateUser(UpdateUser const &packet);
	void parsPacketUpdateFriend(UpdateFriend const &packet);
};

extern ClientSender	*clitmp;
extern ServerSender	*servtmp;

} /* protocol */

} /* babel */