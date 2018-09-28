/*
** EPITECH PROJECT, 2018
** babel
** File description:
** Chopper.cpp
*/

#include "Chopper.hpp"
#include <cstring>

#include <iostream>

namespace nw {

Chopper::Packet::Packet():
	header(static_cast<PackHeader*>(std::malloc(max_packet_length))) {}

Chopper::Packet::Packet(std::uint8_t *buffer, std::size_t len):
	header(static_cast<PackHeader*>(std::malloc(len)))
{
	std::memmove(this->header.get(), buffer, len);
}

//Chopper::Packet::~Packet() {}

std::uint8_t	*Chopper::Packet::getData(void) const
{
	return ((std::uint8_t*) (header.get() + 1));
}

void Chopper::Packet::set(std::uint32_t i, std::uint32_t m, std::uint8_t *buf, std::uint64_t l) {
	this->header->packet_index = i;
	this->header->packet_max = m;
	this->header->packet_length = l;
	std::memmove(this->header.get() + 1, buf, l);
}

std::uint32_t	Chopper::_getByteArrayHash(std::uint8_t *buffer, std::size_t len) {
    std::uint32_t	result = 0;
    const std::uint32_t	prime = 31;

    for (size_t i = 0; i < len; ++i) {
        result = buffer[i] + (result * prime);
    }
    return result;
}

std::shared_ptr<Chopper::ByteArray>
Chopper::_pack(std::vector<std::shared_ptr<Packet>> &toPack) {
	std::shared_ptr<ByteArray>	result(new ByteArray());

	result->length = 0;
	for (auto &itm: toPack)
		result->length += itm->header->packet_length;
	result->buffer = (std::uint8_t*) malloc(result->length);
	
	auto	*off = result->buffer;
	for (auto &itm: toPack) {
		std::memmove(off, itm->getData(), itm->header->packet_length);
		off += itm->header->packet_length;
	}
	return (result);
}

void	Chopper::receivePacket(std::uint8_t *buffer, std::size_t len)
{
	auto pack = std::make_shared<Packet>(buffer, len);
	auto itm = _cache.find(pack->header->id);
	
	if (itm == _cache.end()) {
		_cache[pack->header->id];
		itm = _cache.find(pack->header->id);
		itm->second.reserve(pack->header->packet_max);
	}
	itm->second.push_back(pack);
	if (itm->second.size() == pack->header->packet_max) {
		auto packed = this->_pack(itm->second);
		if (_hooks.onCommandReceived != nullptr)
			_hooks.onCommandReceived(*packed);
	}
}

void
Chopper::sendCommand(std::uint8_t *buffer, std::size_t len) {
	int	max = len / Packet::_maxBufferLen +
			((len % Packet::_maxBufferLen) ? 1 : 0);
	auto	hash = _getByteArrayHash(buffer, len);

	_qu.emplace();
	auto &qi = _qu.back();
	for (std::uint32_t p = 0, i = 0; p < len; p += Packet::_maxBufferLen, ++i) {
		auto itm = std::make_shared<Packet>();
		itm->set(i, max, buffer + p,
			((p + Packet::_maxBufferLen <= len)
				? Packet::_maxBufferLen
				: len % Packet::_maxBufferLen));
		itm->header->id = hash;
		qi.push(itm);
	}
	_sendNextPacket();
}

void
Chopper::_sendNextPacket(void) {
	if (_qu.empty())
		return;
	auto cur = _qu.front();
	auto curPacket = cur.pop();
	_qu.pop();
	if (_hooks.onPacketNeedToBeSend != nullptr) {
		_hooks.onPacketNeedToBeSend(
			reinterpret_cast<std::uint8_t*>(curPacket->header.get()),
			curPacket->header->packet_length +
				sizeof(Packet::PackHeader));
	}
	if (cur.empty() == false)
		_qu.push(cur);
	_sendNextPacket();
}

void
Chopper::QueueItem::push(std::shared_ptr<Packet> const &p) {
	_packQ.push(p);
}

bool
Chopper::QueueItem::empty(void) {
	return (_packQ.empty());
}

std::shared_ptr<Chopper::Packet>
Chopper::QueueItem::pop(void) {
	std::shared_ptr<Packet> res{_packQ.front()};
	_packQ.pop();
	return (res);
}
}