/*
** EPITECH PROJECT, 2018
** babel
** File description:
** Client.cpp
*/

#include "Client.hpp"

namespace srv {

Client::Client(::boost::asio::io_service &ios): _sock(ios) {}

void Client::start(void) {
	_sock.addHandlerOnReadable([this] (std::size_t len) -> int {
		std::uint8_t buffer[len];
		_sock.receive(buffer, len);
		std::cout << std::string((char*) buffer, len) << std::endl;
		return (0);
	});
	_sock.start();
}

}