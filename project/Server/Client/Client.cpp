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
	_sock.addHandlerOnReadable([this] (std::uint8_t *buff, std::size_t len) -> int {
		std::cout << std::string((char*) buff, len) << std::endl;
	});
}

}