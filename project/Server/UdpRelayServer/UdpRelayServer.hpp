/*
** EPITECH PROJECT, 2018
** babel
** File description:
** UdpRelayServer.hpp
*/

#pragma once

#include <memory>
#include <boost/asio.hpp>

namespace srv {

class UdpRelayServer {
public:
	UdpRelayServer(boost::asio::io_context &ios);

	void		start(void);
	std::uint16_t	getListenerPort(void) { return _listenerPort; }
private:
	void		_openSocketOnRandomPort(void);
	void		_startReceive(void);
	void		_handleReceive(const boost::system::error_code& error, std::size_t);

	boost::asio::io_context		&_ios;
	boost::asio::ip::udp::socket	_socket;
	std::unique_ptr<char>		_bufferReceive;
	std::unique_ptr<char>		_bufferSend;
	boost::asio::ip::udp::endpoint	_endpoint;
	std::uint16_t			_listenerPort;
};

}