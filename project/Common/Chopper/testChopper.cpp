#include "Chopper.hpp"
#include <iostream>

#include <stdlib.h>

int main()
{
	nw::Chopper		ch({
		.onCommandReceived = [] (nw::Chopper::ByteArray &bytes) {
			std::cout << "bytes length = " << bytes.length << " --> ";
			for (std::uint32_t i = 0; i < bytes.length; i++) {
				std::cout << (char) bytes.buffer[i];
			}
		},
		.onPacketNeedToBeSend = [&ch] (std::uint8_t *buffer, std::size_t l) {
			std::cout << "packet (len = " << l << ") -> sended" << std::endl;
			ch.receivePacket(buffer, l);
		}
	});
	nw::Chopper::ByteArray	test;
	
	test.buffer = (std::uint8_t*) malloc(64);
	test.length = 64;

	for (std::uint32_t i = 0; i < test.length; i++) {
		test.buffer[i] = i + 33;
	}

	std::cout << "Chop array :" << std::endl;
	// auto vec = nw::Chopper::chop(test);

	// for (auto &itm: *vec) {
	// 	std::cout 	<< "id = " << itm.header->id << " "
	// 			<< itm.header->packet_index << " of "
	// 			<< itm.header->packet_max
	// 			<< " -- length = " << itm.header->packet_length
	// 			<< " data = ";
	// 	for (int i = 0; i < itm.header->packet_length; i++) {
	// 		std::cout << (char) itm.getData()[i];
	// 	}
	// 	std::cout << std::endl;
	// }

	ch.sendCommand(test.buffer, test.length);

	// std::cout << std::endl << "Repack array :" << std::endl;
	// for (auto &itm: *vec) {
	// 	auto pack = std::make_shared<nw::Chopper::Packet>(itm);

	// 	ch.receivePacket(pack);
	// }
	
	std::cout << std::endl;
}