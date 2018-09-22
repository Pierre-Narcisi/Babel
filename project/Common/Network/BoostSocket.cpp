/*
** EPITECH PROJECT, 2018
** babel
** File description:
** BoostSocket.cpp
*/

#include "BoostSocket.hpp"

namespace nw {
namespace boost {

TCPSocket::TCPSocket():
	_ios(new ::boost::asio::io_service()),
	_socket(*_ios),
	_localIos(true) {}

TCPSocket::TCPSocket(::boost::asio::io_service &ios):
	_ios(&ios),
	_socket(*_ios),
	_localIos(false) {}

TCPSocket::~TCPSocket() {
	if (_localIos)
		delete _ios;
}

void	TCPSocket::connect(std::string const &host, std::uint16_t port) {
	::boost::asio::ip::tcp::endpoint endpoint(::boost::asio::ip::address::from_string(host), port);

	_socket.connect(endpoint);
}

std::size_t	TCPSocket::send(std::uint8_t *buff, std::size_t len) {
	return _socket.write_some(::boost::asio::buffer(buff, len));
}

std::size_t	TCPSocket::receive(std::uint8_t *buff, std::size_t len) {
	return	_socket.read_some(::boost::asio::buffer(buff, len));
}

std::size_t	TCPSocket::available(void) const {
	return _socket.available();
}

}
}