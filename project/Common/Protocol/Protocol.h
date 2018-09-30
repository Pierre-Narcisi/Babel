/*
** EPITECH PROJECT, 2018
** babel
** File description:
** Protocol.h
*/

#pragma once

#include <cstddef>
#include <string>

#ifdef IMPL_PACKCONST
#undef IMPL_PACKCONST
#endif
#define IMPL_PACKCONST(T) explicit T(): Packet(sizeof(T), Packet::Type::T) {}

#ifdef IMPL_PACKDYN
#undef IMPL_PACKDYN
#endif
#define IMPL_PACKDYN(T) \
	void *operator new[](std::size_t s) { \
		auto	psize = sizeof(T) + s + 1; \
		auto	*ptr = reinterpret_cast<T*>(::operator new(psize)); \
		ptr->packetSize = psize; \
		ptr->type = Packet::Type::T; \
		return ptr; \
	}



namespace babel {

namespace protocol {

/* Common */

struct Packet {
	enum class Type {
        Respond = 1,
        Connect = 2,
        GetMessages = 3,
        SendMessage = 4,
        UpdateLogo = 5,
        UpdateUser = 6,
        UpdateFriend = 7,
        UpdateClient = 8,
        UpdateFriendState = 9,
        UpdateMessage = 10,
        CliUpdateCall = 11,
        ServUpdateCall = 12
	} type;
	Packet(): packetSize(sizeof(Packet)) {}
	Packet(std::size_t s, Type t): type(t), packetSize(s) {}
	std::size_t packetSize;
};

struct Respond : public Packet {
	IMPL_PACKCONST(Respond)
	enum Type : bool {OK = true, KO = false};
	Packet::Type	previous;
	Respond::Type	respond;
};

/* Client -> Server */
struct Connect : public Packet {
	IMPL_PACKCONST(Connect)
	char		username[128];
	char		password[128];
	bool		needRegister;
};

struct GetMessages : public Packet {
	IMPL_PACKCONST(GetMessages)
	char		username[128];
	std::size_t	start;
	std::size_t	number;
};

struct UpdateLogo : public Packet {
	std::size_t	size;
	char		buffer[];

	IMPL_PACKDYN(UpdateLogo);
};

struct UpdateUser : public Packet {
	IMPL_PACKCONST(UpdateUser)
	char		username[128];
	char		password[128];
};

struct UpdateFriend : public Packet {
	IMPL_PACKCONST(UpdateFriend)
	enum class What {Update, Erase};
	What		what;
	char		username[128];
	char		name[128];
};

struct SendMessage : public Packet {
	char		username[128];
	std::size_t	size;
	char		buffer[]; /* message */

	IMPL_PACKDYN(SendMessage)
};

/* Server -> Client */
struct UpdateClient : public Packet {
	char		username[128];
	std::size_t	size;
	char		buffer[]; /* icon */

	IMPL_PACKDYN(UpdateClient)
};

struct UpdateFriendState : public Packet {
	bool		state;
	char		username[128];
	char		name[128];
	std::size_t	size;
	char		buffer[]; /* icon */

	IMPL_PACKDYN(UpdateFriendState);
};

struct UpdateMessage : public Packet {
	IMPL_PACKCONST(UpdateMessage)
	struct Message {
		std::size_t	size;
		char		buffer[];
	};
	char		username[128];
	std::size_t	nbMessage;
	Message		messages[];
};

struct CliUpdateCall : public Packet {
	IMPL_PACKCONST(CliUpdateCall)
};

struct ServUpdateCall : public Packet {
	IMPL_PACKCONST(ServUpdateCall)
};

class Sender {
public:
	virtual void receivePacket(Packet &packet) = 0;
	virtual void sendPacket(Packet &packet) = 0;

    static std::string humanReadable(Packet::Type packType);
protected:
	void parsPacketRespond(Respond const &packet); /* done */
};

} /* protocol */

} /* babel */
