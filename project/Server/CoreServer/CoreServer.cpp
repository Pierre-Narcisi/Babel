/*
** EPITECH PROJECT, 2018
** babel
** File description:
** CoreServer.cpp
*/

#include <iostream>
#include "Constant.hpp"
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
		[this, newClient] (const boost::system::error_code& e) {
			this->_handleAccept(newClient, e);
			auto it = this->_clts.insert(this->_clts.end(), newClient);
			newClient->setOnDisconnect([this, it] {
				std::cout << "Client disconnected" << std::endl;
				this->_clts.erase(it);
			});
		});
}

	
void CoreServer::_handleAccept(Client::ptr newClient, const boost::system::error_code& error)
{
	if (!error) {
		std::cout << "New client connected" << std::endl;
		newClient->start();
		this->_startAccept();
	} else {
		throw std::runtime_error(error.message().c_str());
	}
}

CoreServer::CoreArgs::CoreArgs(int ac, char **av) {
	common::Opts	opts(ac, av);

	opts.setUsage("Usage", std::string(av[0]) + " [arguments...]");
	opts.setArgsTitle("Available Arguments");
	opts.setOptions({
		{"help", 'h', common::Opts::noArg(), "Show this help"},
		{"port", 'p', common::Opts::makeInt(constant::defPort), "Listening port"},
		{"db-filename", 'f', common::Opts::makeString(constant::defDbFileName), "database filename"}
	});

	opts.parse();

	if (opts["help"]->count()) {
		std::cout << opts << std::endl;
		exit(0);
	}

	_port = opts["port"]->as<common::Opts::Int>();
	_dbFileName = opts["db-filename"]->as<common::Opts::String>();
}

}