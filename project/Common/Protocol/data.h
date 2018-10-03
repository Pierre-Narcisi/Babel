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

namespace protocol {

namespace data {

struct ConnectReponse {
	std::uint64_t	id;
	std::uint16_t	udpRelayPort;
} PACKET_ATTRIBUTE;

}

}