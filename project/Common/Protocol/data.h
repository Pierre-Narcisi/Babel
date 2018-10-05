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
#define PACKET_ATTRIBUTE __attribute__((packed, gcc_struct))

namespace proto {

namespace data {

struct ConnectRespond {
	std::uint64_t	id;
} PACKET_ATTRIBUTE;

struct GetClientIpRespond {
	char		username[128];
	std::uint32_t	ip;
}	PACKET_ATTRIBUTE;

}

}