/*
** EPITECH PROJECT, 2018
** babel
** File description:
** CoreServer.cpp
*/

#include <iostream>
#include "boost/asio.hpp"
#include "Opts/Opts.hpp"
#include "CoreServer.hpp"

namespace srv {

using btcp = ::boost::asio::ip::tcp;
CoreServer::CoreServer(int ac, char **av):
	_args(std::make_unique<CoreArgs>(ac, av)),
	_acceptor(_ios, btcp::endpoint(btcp::v4(), _args->port())) {}

void CoreServer::start(void)
{
	_acceptor.listen();

	std::cout << "Start listening on " << _args->port() << std::endl;
	_startAccept();
	_ios.run();
}

void	CoreServer::_startAccept(void) {
	Client::ptr newClient = Client::create(_acceptor.get_io_service());

	_acceptor.async_accept(newClient->getSocket().getBoostSocket(),
		boost::bind(&CoreServer::_handleAccept, this, newClient,
			boost::asio::placeholders::error));
}

	
void CoreServer::_handleAccept(Client::ptr newClient, const boost::system::error_code& error)
{
	if (!error) {
		std::cout << "New client connected" << std::endl;
		newClient->start();
		//newClient->getSocket().send((std::uint8_t*)"Salut :)\n", 9);
		this->_startAccept();
	} else {
		throw std::runtime_error(error.message().c_str());
	}
}

CoreServer::CoreArgs::CoreArgs(int ac, char **av) {
	common::Opts opt(ac, av);
}

}