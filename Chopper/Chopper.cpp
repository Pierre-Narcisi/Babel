/*
** EPITECH PROJECT, 2018
** babel
** File description:
** Chopper.cpp
*/

#include "Chopper.hpp"
#include <cstring>

#include <iostream>

namespace CC {

Chopper::Packet::Packet():
	header(static_cast<PackHeader*>(std::malloc(max_packet_length))) {}

Chopper::Packet::~Packet() {
	free(this->header);
}

std::uint8_t	*Chopper::Packet::getData(void) const
{
	return ((std::uint8_t*) (header + 1));
}

void Chopper::Packet::set(std::uint32_t i, std::uint32_t m, std::uint8_t *buf, std::uint64_t l) {
	this->header->packet_index = i;
	this->header->packet_max = m;
	this->header->packet_length = l;
	std::memmove(this->header + 1, buf, l);
}

std::shared_ptr<std::vector<Chopper::Packet>>
Chopper::chop(Chopper::ByteArray &bytes) {
	int	max = bytes.length / Packet::_maxBufferLen +
			((bytes.length % Packet::_maxBufferLen) ? 1 : 0);
	auto	result = std::make_shared<std::vector<Packet>>(max);

	for (std::uint32_t p = 0, i = 0; p < bytes.length; p += Packet::_maxBufferLen, ++i) {
		(*result)[i].set(i, max, bytes.buffer + p,
			((p + Packet::_maxBufferLen <= bytes.length)
				? Packet::_maxBufferLen
				: bytes.length % Packet::_maxBufferLen));
	}
	return (result);
}

std::shared_ptr<Chopper::ByteArray>
Chopper::pack(std::vector<Packet> &toPack) {
	std::shared_ptr<ByteArray>	result(new ByteArray());

	result->length = 0;
	for (auto &itm: toPack)
		result->length += itm.header->packet_length;
	result->buffer = (std::uint8_t*) malloc(result->length);
	
	auto	*off = result->buffer;
	for (auto &itm: toPack) {
		std::memmove(off, itm.getData(), itm.header->packet_length);
		off += itm.header->packet_length;
	}
	return (result);
}

}