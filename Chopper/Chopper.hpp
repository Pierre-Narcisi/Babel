/*
** EPITECH PROJECT, 2018
** babel
** File description:
** Chopper.hpp
*/

#include <cinttypes>
#include <vector>
#include <cstdlib>
#include <memory>

namespace CC {

#ifdef DEBUG_MAX_PACKET_LEN
	static const int max_packet_length = DEBUG_MAX_PACKET_LEN;
#else
	static const int max_packet_length = 2048;
#endif

class Chopper {
public:
	class Packet {
	public:
		Packet();
		Packet(Packet const &) = default;
		~Packet();

		void set(std::uint32_t i, std::uint32_t m, std::uint8_t *buf, std::uint64_t l); 
		
		std::uint8_t	*getData(void) const;

		struct	PackHeader{
			std::uint32_t	command_hash;
			std::uint32_t	packet_index;
			std::uint32_t	packet_max;
			std::uint16_t	packet_length;
		} __attribute__((packed));

		PackHeader	*header;

		static const uint16_t	_maxBufferLen = max_packet_length - sizeof(*header);
	};

	struct ByteArray {
		~ByteArray() { free(buffer); }

		std::uint64_t	length;
		std::uint8_t	*buffer;
	};

	

	static std::shared_ptr<std::vector<Packet>>
		chop(ByteArray &bytes);
	static std::shared_ptr<ByteArray>
		pack(std::vector<Packet> &toPack);
};

}