/*
** EPITECH PROJECT, 2018
** babel
** File description:
** Chopper.cpp
*/

#include <chrono>
#include <thread>
#include <cstring>
#include "Chopper.hpp"

#include <iostream>

#define MAGIC_KEY 0xAB7645BA

namespace nw {

Chopper::Packet::Packet():
	header(static_cast<PackHeader*>(::operator new(max_packet_length))) {}

Chopper::Packet::Packet(std::uint8_t *buffer, std::size_t len):
	header(static_cast<PackHeader*>(::operator new(len)))
{
    std::memmove(this->header, buffer, len);
}

Chopper::Chopper(Hooks const &h): _sock(*(reinterpret_cast<ASocket*>(0))), _hooks(h) {
    std::memset(&_save, 0, sizeof(_save));
}

Chopper::Chopper(ASocket &sock, Hooks const &h): _sock(sock), _hooks(h) {
    std::memset(&_save, 0, sizeof(_save));
    _sock.setOnReadable([this] (std::size_t len) -> int {
        std::uint8_t	*buff = (_save._buf
                                 ? _save._buf
                                 : new std::uint8_t[max_packet_length]);
        auto	*h = reinterpret_cast<Packet::PackHeader*>(buff);
		std::cerr << "Can i read " << len << "?" << std::endl;
        std::size_t l;
        if (_save._buf && _save._headerIncomplete) {
            l = _sock.receive(buff + _save._l, _save._rest) + _save._l;
            _save._buf = nullptr;
        } else if (!_save._buf) {
            l = _sock.receive(buff, sizeof(*h));
        } else {
            l = _save._l;
        }
        if (l < sizeof(*h)) {
            _save._buf = buff;
            _save._headerIncomplete = true;
            _save._l = l;
            _save._rest = sizeof(*h) - l;
            return (0);
        }
        std::size_t pLen;
        if (_save._buf) {
            pLen = _sock.receive(
                        buff + sizeof(*h) + _save._pLen,
                        _save._rest) + _save._pLen;
        } else {
            pLen = _sock.receive(buff + sizeof(*h), h->packet_length);
        }
        if (pLen < h->packet_length) {
            _save._buf = buff;
            _save._headerIncomplete = false;
            _save._l = l;
            _save._pLen = pLen;
            _save._rest = h->packet_length - pLen;
            std::cerr << pLen << " " << h->packet_length << std::endl;
            return (0);
        }
        l += pLen;
		std::cerr << "Yes! " << l << " bytes" << std::endl;
		this->receivePacket(buff, l);
		delete buff;
        std::memset(&_save, 0, sizeof(_save));
		return (0);
	});
}

//Chopper::Packet::~Packet() {}

std::uint8_t	*Chopper::Packet::getData(void) const
{
    return (reinterpret_cast<std::uint8_t*>(header + 1));
}

void Chopper::Packet::set(std::uint32_t i, std::uint32_t m, std::uint8_t *buf, std::uint64_t l) {
	this->header->packet_index = i;
	this->header->packet_max = m;
	this->header->packet_length = l;
	this->header->magic = MAGIC_KEY;
	std::memmove(this->header + 1, buf, l);
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
	result->buffer = (std::uint8_t*) ::operator new(result->length);
	
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
		_cache.erase(itm);
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
		auto itm = std::shared_ptr<Packet>(new Packet());

		itm->set(i, max, buffer + p,
			((p + Packet::_maxBufferLen <= len)
				? Packet::_maxBufferLen
				: len % Packet::_maxBufferLen));
		itm->header->id = hash;
		std::cerr << "new sub pack " << itm->header->id
				<< ": " << itm->header->packet_index
				<< " of " <<  itm->header->packet_max
				<< std::endl;
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
	std::cerr << "Chopper send (" << curPacket->header->packet_length
		<< ")" << std::endl;
	_sock.send(
		reinterpret_cast<std::uint8_t*>(curPacket->header),
		curPacket->header->packet_length +
			sizeof(Packet::PackHeader));
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
