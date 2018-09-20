#include "Chopper.hpp"
#include <iostream>

#include <stdlib.h>

int main()
{
	CC::Chopper::ByteArray	test;
	
	test.buffer = (std::uint8_t*) malloc(64);
	test.length = 64;

	for (std::uint32_t i = 0; i < test.length; i++) {
		test.buffer[i] = i + 33;
	}

	std::cout << "Chop array :" << std::endl;
	auto vec = CC::Chopper::chop(test);

	for (auto &itm: *vec) {
		std::cout 	<< itm.header->packet_index << " of "
				<< itm.header->packet_max
				<< " -- length = " << itm.header->packet_length
				<< " data = ";
		for (int i = 0; i < itm.header->packet_length; i++) {
			std::cout << (char) itm.getData()[i];
		}
		std::cout << std::endl;
	}

	std::cout << std::endl << "Repack array :" << std::endl;
	auto bytes = CC::Chopper::pack(*vec);
	std::cout << "bytes length = " << bytes->length << " --> ";
	for (std::uint32_t i = 0; i < bytes->length; i++) {
		std::cout << (char) bytes->buffer[i];
	}
	std::cout << std::endl;
}