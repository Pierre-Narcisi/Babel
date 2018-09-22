/*
** EPITECH PROJECT, 2018
** babel
** File description:
** Client.hpp
*/

#pragma once

#include <boost/enable_shared_from_this.hpp>
#include <boost/shared_ptr.hpp>
#include "Network/BoostSocket.hpp"

namespace srv {

class Client: public ::boost::enable_shared_from_this<Client> {
public:
	using ptr = ::boost::shared_ptr<Client>;

	static inline ptr	create(::boost::asio::io_service& ios) {
		return ptr(new Client(ios));
	}

	inline ::boost::asio::ip::tcp::socket
			&getBoostSocket(void) { return _sock.getBoostSocket(); }

	void	start(void);
private:
	explicit Client(::boost::asio::io_service &ios);

	nw::boost::TCPSocket	_sock;
};

}