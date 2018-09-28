/*
** EPITECH PROJECT, 2018
** babel
** File description:
** Chopper.hpp
*/

#pragma once

#include <cinttypes>
#include <vector>
#include <cstdlib>
#include <memory>
#include <unordered_map>
#include <functional>
#include <queue>

#ifdef DEBUG_MAX_PACKET_LEN
	static const int max_packet_length = DEBUG_MAX_PACKET_LEN;
#else
	static const int max_packet_length = 2048;
#endif

namespace nw {


class Chopper {
private:
	class Packet;

	struct QueueItem;
public:
	struct ByteArray;
	struct Hooks {
		std::function<void(ByteArray &)> onCommandReceived;
		std::function<void(std::uint8_t*, std::size_t)> onPacketNeedToBeSend;
	};
public:
	Chopper(Hooks &&h): _hooks(h) {}

	void	receivePacket(std::uint8_t *buffer, std::size_t len);
	void	sendCommand(std::uint8_t *buffer, std::size_t len);

	static inline const std::size_t
		getMaxPacketSize(void) { return max_packet_length; }
private:
	void			_sendNextPacket(void);
	static std::uint32_t	_getByteArrayHash(std::uint8_t *buffer, std::size_t len);
	static std::shared_ptr<ByteArray>
				_pack(std::vector<std::shared_ptr<Packet>> &toPack);

	Hooks			_hooks;
	std::queue<QueueItem>	_qu;
	std::unordered_map<std::uint32_t, std::vector<std::shared_ptr<Packet>>>	_cache;
};

class Chopper::Packet  {
public:
	Packet();
	Packet(std::uint8_t *buffer, std::size_t len);
	Packet(Packet const &from) = default;
	Packet &operator=(Packet &) = default;
	~Packet() = default;

	void set(std::uint32_t i, std::uint32_t m, std::uint8_t *buf, std::uint64_t l); 
	
	std::uint8_t	*getData(void) const;

	struct	PackHeader{
		static void operator delete(void* ptr) {
			free(ptr);
		}
		std::size_t	id;
		std::uint32_t	packet_index;
		std::uint32_t	packet_max;
		std::uint16_t	packet_length;
	} __attribute__((packed));

	std::shared_ptr<PackHeader>	header;

	static const uint16_t	_maxBufferLen = max_packet_length - sizeof(*header);
};

class Chopper::QueueItem {
public:
	QueueItem() = default;

	inline void push(std::shared_ptr<Packet> const &);
	inline std::shared_ptr<Packet> pop(void);
	inline bool empty(void);
private:	
	std::queue<std::shared_ptr<Packet>> _packQ;
};

struct Chopper::ByteArray {
	~ByteArray() { free(buffer); }

	std::uint64_t	length;
	std::uint8_t	*buffer;
};

}