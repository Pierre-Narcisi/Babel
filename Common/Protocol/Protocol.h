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
#include <memory>
#include "data.h"

#ifdef IMPL_PACKCONST
# undef IMPL_PACKCONST
#endif
#define IMPL_PACKCONST(T) explicit T(): Packet(sizeof(T), Packet::Type::T) {}

#ifdef IMPL_PACKDYN
# undef IMPL_PACKDYN
#endif
#define IMPL_PACKDYN(T) \
	static std::unique_ptr<T> create(std::size_t s) { \
		auto	psize = sizeof(T) + s + 1; \
		auto	*ptr = reinterpret_cast<T*>(::operator new(psize)); \
		ptr->packetSize = psize; \
		ptr->size = s; \
		ptr->type = Packet::Type::T; \
		return std::unique_ptr<T>(ptr); \
	}
	
namespace babel {

namespace protocol {

/* Common */

#ifdef _WIN32
# pragma pack(push,1)
#endif

struct Packet {
    enum class Type : std::uint8_t {
        Respond,
        Connect,
        GetMessages,
        SendMessage,
	CallRequest,
	CallRespond,
	CallEnd,
	GetClientIp,
        UpdateLogo,
        UpdateUser,
        UpdateFriend,
        UpdateClient,
        UpdateFriendState,
        UpdateMessage,
        CliUpdateCall,
        ServUpdateCall,
	VoicePacket
	} type;

	Packet() {}
	Packet(std::uint64_t s, Type t): type(t), packetSize(s) {}

	std::uint64_t packetSize;
} PACKET_ATTRIBUTE;

struct VoicePacket : public Packet {
	std::uint64_t	size;
	std::uint64_t	length;
	char		data[];
	IMPL_PACKDYN(VoicePacket);
}	PACKET_ATTRIBUTE;

struct Respond : public Packet {
	enum Type : bool {OK = true, KO = false};
	Packet::Type	previous;
	Respond::Type	respond;
	std::uint64_t	size;
	char		data[];
	IMPL_PACKDYN(Respond);
} PACKET_ATTRIBUTE;

/* Client -> Server */
struct Connect : public Packet {
	IMPL_PACKCONST(Connect)
	enum Type : char {CONNECT, CREATE};
	Connect::Type	connectionType;
	char		username[128];
	char		password[128];
	bool		needRegister;
} PACKET_ATTRIBUTE;

struct GetMessages : public Packet {
	IMPL_PACKCONST(GetMessages)
	char		username[128];
	std::uint64_t	start;
	std::uint64_t	number;
} PACKET_ATTRIBUTE;

struct CallRequest : public Packet {
	IMPL_PACKCONST(CallRequest)
	char		username[128];
} PACKET_ATTRIBUTE;

struct CallEnd : public Packet {
	IMPL_PACKCONST(CallEnd)
	char		username[128];
} PACKET_ATTRIBUTE;

struct CallRespond : public Packet {
	IMPL_PACKCONST(CallRespond)
	enum Type : bool {ACCEPT = true, REJECT = false};
    CallRespond::Type	respond;
    char                fromUsername[128];
    char                toUsername[128];
} PACKET_ATTRIBUTE;

struct GetClientIp : public Packet {
	IMPL_PACKCONST(GetClientIp)
	char		username[128];
} PACKET_ATTRIBUTE;

struct UpdateLogo : public Packet {
	char		extend[8];
	std::uint64_t	size;
	char		buffer[];
	IMPL_PACKDYN(UpdateLogo);
} PACKET_ATTRIBUTE;

struct UpdateUser : public Packet {
	IMPL_PACKCONST(UpdateUser)
	char		password[128];
	char		newpassword[128];
} PACKET_ATTRIBUTE;

struct UpdateFriend : public Packet {
	IMPL_PACKCONST(UpdateFriend)
	enum class What {NEW, UPDATE, ERASE};
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
	bool			erase = false;
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
	char			data[];
	Message			*messages(void) { return reinterpret_cast<Message*>(data); }
} PACKET_ATTRIBUTE;

struct CliUpdateCall : public Packet {
	IMPL_PACKCONST(CliUpdateCall)
} PACKET_ATTRIBUTE;

struct ServUpdateCall : public Packet {
	IMPL_PACKCONST(ServUpdateCall)
} PACKET_ATTRIBUTE;

#ifdef _WIN32
# pragma pack(pop)
#endif

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
