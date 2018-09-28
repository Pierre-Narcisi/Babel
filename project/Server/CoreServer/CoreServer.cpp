/*
** EPITECH PROJECT, 2018
** babel
** File description:
** CoreServer.cpp
*/

#include <iostream>
#include <boost/thread.hpp>
#include <boost/asio.hpp>
#include "Constant.hpp"
#include "Opts/Opts.hpp"
#include "CoreServer.hpp"

namespace srv {

using btcp = ::boost::asio::ip::tcp;
CoreServer::CoreServer(int ac, char **av):
		_args(std::make_unique<CoreArgs>(ac, av)),
		_acceptor(_ios, btcp::endpoint(btcp::v4(), _args->port())),
		_signals(_ios) {
	_signals.add(SIGINT);
	_signals.add(SIGTERM);
#if defined(SIGQUIT)
	_signals.add(SIGQUIT);
#endif // defined(SIGQUIT)
	_signals.async_wait(boost::bind(&CoreServer::_handleStop, this));

	_acceptor.listen();
	_startAccept();
}

CoreServer::~CoreServer() {
	std::cout << "Server stoped" << std::endl;
}

void CoreServer::_handleStop(void)
{
  _ios.stop();
}

void CoreServer::start(void)
{
	std::vector<::boost::thread>	_threads;

	_threads.reserve(_args->threadNbr());
	for (int i = 0; i < _args->threadNbr(); i++)
		_threads.emplace_back(::boost::bind(
				&::boost::asio::io_service::run,
				&_ios));
	std::cout << "Start listening on " << _args->port() << std::endl;
	_ios.run();
	for (auto &t: _threads)
		t.join();
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
		{"thread-nbr", 't', common::Opts::makeInt(constant::defThreadNbr), "Number of Threads"},
		{"db-filename", 'f', common::Opts::makeString(constant::defDbFileName), "database filename"}
	});

	opts.parse();

	if (opts["help"]->count()) {
		std::cout << opts << std::endl;
		exit(0);
	}

	_port = opts["port"]->as<common::Opts::Int>();
	_threadNbr = opts["thread-nbr"]->as<common::Opts::Int>();
	_dbFileName = opts["db-filename"]->as<common::Opts::String>();
}

}