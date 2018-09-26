/*
** EPITECH PROJECT, 2018
** babel
** File description:
** BoostSocket.cpp
*/

#include "Network/BoostSocket.hpp"

namespace nw {
namespace boost {

TCPSocket::TCPSocket():
	_ios(new ::boost::asio::io_service()),
	_socket(*_ios),
	_localIos(true) { _start(); }

TCPSocket::TCPSocket(::boost::asio::io_service &ios):
	_ios(&ios),
	_socket(*_ios),
	_localIos(false) { _start(); }

TCPSocket::~TCPSocket() {
	if (_localIos)
		delete _ios;
}

void	TCPSocket::_start(void) {
	_socket.async_receive(::boost::asio::buffer(_buffer.get(), Chopper::getMaxPacketSize()),
		::boost::bind(&TCPSocket::_onReceiveHandler, this,
			::boost::asio::placeholders::error,
			::boost::asio::placeholders::bytes_transferred));
}

void	TCPSocket::connect(std::string const &host, std::uint16_t port) {
	::boost::asio::ip::tcp::endpoint endpoint(::boost::asio::ip::address::from_string(host), port);

	_socket.connect(endpoint);
}

void	TCPSocket::_onReceiveHandler(::boost::system::error_code const &e, std::size_t available) {
	for (auto &it: _hdls) {
		it.operator()(reinterpret_cast<std::uint8_t*>(_buffer.get()), available);
	}
	_socket.async_receive(::boost::asio::buffer(_buffer.get(), Chopper::getMaxPacketSize()),
		::boost::bind(&TCPSocket::_onReceiveHandler, this,
			::boost::asio::placeholders::error,
			::boost::asio::placeholders::bytes_transferred));
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