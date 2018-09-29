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
	_sock.addHandlerOnReadable(::boost::bind(
			&Client::_onReadableHandler,
			this,
			::boost::placeholders::_1));
	_sock.start();
}

int Client::_onReadableHandler(std::size_t len) {
	std::uint8_t buffer[len];
	_sock.receive(buffer, len);
	std::cout << std::string((char*) buffer, len) << std::endl;
	return (0);
}

}