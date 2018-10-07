/*
** EPITECH PROJECT, 2018
** babel
** File description:
** data.h
*/

#pragma once

#include <cinttypes>

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

#ifdef PACKET_ATTRIBUTE
# undef PACKET_ATTRIBUTE
#endif
#ifdef __linux__
# define PACKET_ATTRIBUTE __attribute__((packed, ms_struct))
#else
# define PACKET_ATTRIBUTE //windows
#endif

namespace proto {

namespace data {
#ifdef _WIN32
# pragma pack(push,1)
#endif
struct ConnectRespond {
	std::uint64_t	id;
}	PACKET_ATTRIBUTE;

struct GetClientIpRespond {
	char		username[128];
	std::uint32_t	ip;
}	PACKET_ATTRIBUTE;

#ifdef _WIN32
# pragma pack(pop)
#endif

}

}