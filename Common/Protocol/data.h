/*
** EPITECH PROJECT, 2018
** babel
** File description:
** data.h
*/

#pragma once

#include <cinttypes>

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
} PACKET_ATTRIBUTE;

struct GetClientIpRespond {
	char		username[128];
	std::uint32_t	ip;
}	PACKET_ATTRIBUTE;

#ifdef _WIN32
# pragma pack(pop)
#endif

}

}