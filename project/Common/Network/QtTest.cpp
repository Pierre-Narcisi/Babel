/*
** EPITECH PROJECT, 2018
** babel
** File description:
** test.cpp
*/

#include <iostream>
#include <unistd.h>
#include "QtSocket.hpp"

int main() {
	nw::qt::TCPSocket	sock(nullptr);
	//auto			&sock = reinterpret_cast<nw::ISocket&>(__sock);
	std::size_t		s;

	sock.connect("127.0.0.1", 5575);
	sock.send((std::uint8_t*) "Salut\n", 6);
	while (1) {
		s = 1024;
		if ((s = sock.available()) != 0) {
			std::cout << sock.available() << std::endl;
			char buffer[s + 1];

			sock.receive((std::uint8_t*) buffer, s);
			buffer[s] = 0;
			std::cout << buffer;
		}
		usleep(500000);
	}
	return (0);
}