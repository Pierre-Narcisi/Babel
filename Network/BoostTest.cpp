/*
** EPITECH PROJECT, 2018
** babel
** File description:
** test.cpp
*/

#include <iostream>
#include <unistd.h>
#include "BoostSocket.hpp"

int main() {
	nw::boost::TCPSocket	__sock;
	auto			&sock = reinterpret_cast<nw::ISocket&>(__sock);
	std::size_t		s;

	__sock.connect("127.0.0.1", 5555);
	sock.send((std::uint8_t*) "Salut\n", 6);
	while (1) {
		if ((s = sock.available()) != 0) {
			char buffer[s + 1];

			sock.receive((std::uint8_t*) buffer, s);
			buffer[s] = 0;
			std::cout << buffer;
		}
		usleep(100);
	}
	return (0);
}