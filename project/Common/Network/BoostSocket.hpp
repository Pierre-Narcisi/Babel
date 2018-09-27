/*
** EPITECH PROJECT, 2018
** babel
** File description:
** BoostSocket.hpp
*/

#pragma once

#include <boost/bind.hpp>
#include <boost/asio.hpp>
#include "INetwork.hpp"

namespace nw {
namespace boost {

class TCPSocket: ITCPSocket {
public:
	TCPSocket();
	TCPSocket(::boost::asio::io_service &srv);
	~TCPSocket();
	
	virtual std::size_t	send(std::uint8_t *buff, std::size_t len) final;
	virtual std::size_t	receive(std::uint8_t *buff, std::size_t len) final;
	virtual std::size_t	available(void) const final;
	virtual void		connect(std::string const &host, std::uint16_t port) final;

	inline ::boost::asio::ip::tcp::socket
				&getBoostSocket(void) { return _socket; } 
private:
	::boost::asio::io_service	*_ios;
	::boost::asio::ip::tcp::socket	_socket;
	bool				_localIos;
};

}
}