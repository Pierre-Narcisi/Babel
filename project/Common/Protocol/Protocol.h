/*
** EPITECH PROJECT, 2018
** babel
** File description:
** Protocol.h
*/

#pragma once

#include <cstddef>
#include <string>
#include <iostream>
#include "data.h"

#ifdef IMPL_PACKCONST
# undef IMPL_PACKCONST
#endif
#define IMPL_PACKCONST(T) explicit T(): Packet(sizeof(T), Packet::Type::T) {}

#ifdef IMPL_PACKDYN
# undef IMPL_PACKDYN
#endif
#define IMPL_PACKDYN(T) \
    static void *operator new(std::size_t, std::size_t s) { \
        auto	psize = sizeof(T) + s + 1; \
		auto	*ptr = reinterpret_cast<T*>(::operator new(psize)); \
		ptr->packetSize = psize; \
		ptr->size = s; \
		ptr->type = Packet::Type::T; \
		return ptr; \
	} \
    static void operator delete(void *ptr) { \
		::operator delete(ptr); \
	}
	
namespace babel {

namespace protocol {

/* Common */

struct Packet {
    enum class Type : std::uint8_t {
        Respond,
        Connect,
        GetMessages,
        SendMessage,
        UpdateLogo,
        UpdateUser,
        UpdateFriend,
        UpdateClient,
        UpdateFriendState,
        UpdateMessage,
        CliUpdateCall,
        ServUpdateCall
	} type;

	Packet() {}
    Packet(std::uint64_t s, Type t): type(t), packetSize(s) {}

    std::uint64_t packetSize;
} PACKET_ATTRIBUTE;

struct Respond : public Packet {
	enum Type : bool {OK = true, KO = false};
	Packet::Type	previous;
	Respond::Type	respond;
	std::uint64_t	size;
	char            data[];
	IMPL_PACKDYN(Respond);
} PACKET_ATTRIBUTE;

/* Client -> Server */
struct Connect : public Packet {
	IMPL_PACKCONST(Connect)
	char		username[128];
	char		password[128];
	bool		needRegister;
} PACKET_ATTRIBUTE;

struct GetMessages : public Packet {
	IMPL_PACKCONST(GetMessages)
	char			username[128];
	std::uint64_t	start;
	std::uint64_t	number;
} PACKET_ATTRIBUTE;

struct UpdateLogo : public Packet {
	std::uint64_t	size;
    char			buffer[];
    IMPL_PACKDYN(UpdateLogo);
} PACKET_ATTRIBUTE;

struct UpdateUser : public Packet {
	IMPL_PACKCONST(UpdateUser)
	char		username[128];
	char		password[128];
} PACKET_ATTRIBUTE;

struct UpdateFriend : public Packet {
	IMPL_PACKCONST(UpdateFriend)
	enum class What {Update, Erase};
	What		what;
	char		username[128];
	char		name[128];
} PACKET_ATTRIBUTE;

struct SendMessage : public Packet {
	char			username[128];
	std::uint64_t	size;
	char			buffer[]; /* message */

	IMPL_PACKDYN(SendMessage)
} PACKET_ATTRIBUTE;

/* Server -> Client */
struct UpdateClient : public Packet {
	char			username[128];
	std::uint64_t	size;
	char			buffer[]; /* icon */

	IMPL_PACKDYN(UpdateClient)
} PACKET_ATTRIBUTE;

struct UpdateFriendState : public Packet {
	bool			state;
	char			username[128];
	char			name[128];
	std::uint64_t		size;
	char			buffer[]; /* icon */

	IMPL_PACKDYN(UpdateFriendState);
} PACKET_ATTRIBUTE;

struct UpdateMessage : public Packet {
	IMPL_PACKCONST(UpdateMessage)
	struct Message {
		std::uint64_t	size;
		char			buffer[];
	} PACKET_ATTRIBUTE;
	char			username[128];
	std::uint64_t	nbMessage;
	Message			messages[];
} PACKET_ATTRIBUTE;

struct CliUpdateCall : public Packet {
	IMPL_PACKCONST(CliUpdateCall)
} PACKET_ATTRIBUTE;

struct ServUpdateCall : public Packet {
	IMPL_PACKCONST(ServUpdateCall)
} PACKET_ATTRIBUTE;

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
