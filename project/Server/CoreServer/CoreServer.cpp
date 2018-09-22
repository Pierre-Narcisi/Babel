/*
** EPITECH PROJECT, 2018
** babel
** File description:
** CoreServer.cpp
*/

#include <iostream>
#include "boost/program_options.hpp"
#include "boost/asio.hpp"
#include "CoreServer.hpp"

namespace srv {

using btcp = ::boost::asio::ip::tcp;
CoreServer::CoreServer(int ac, char **av):
	_args(std::make_unique<CoreArgs>(ac, av)),
	_acceptor(_ios, btcp::endpoint(btcp::v4(), _args->port())) {}

void CoreServer::start(void)
{
	Client::ptr newClient = Client::create(_acceptor.get_io_service());

	_acceptor.listen();
	_acceptor.async_accept(newClient->getSocket().getBoostSocket(),
		boost::bind(&CoreServer::handleAccept, this, newClient,
			boost::asio::placeholders::error));
	_ios.run();
}
	
void CoreServer::handleAccept(Client::ptr newClient, const boost::system::error_code& error)
{
	if (!error) {
		std::cout << "New client connected" << std::endl;
		newClient->start();
		//newClient->getSocket().send((std::uint8_t*)"Salut :)\n", 9);
		this->start();
	} else {
		throw std::runtime_error(error.message().c_str());
	}
}

namespace po = ::boost::program_options;
CoreServer::CoreArgs::CoreArgs(int ac, char **av) {
	po::options_description	desc("Available options");

	desc.add_options()
		("help", "Show this help")
		("port", po::value<std::uint16_t>(), "Set custom port (default : 5555)")
		("bdd_filename", po::value<std::string>(), "Set custom bdd (default : \".bdd\")")
	;

	po::variables_map vm;
	po::store(po::parse_command_line(ac, av, desc), vm);
	po::notify(vm);

	if (vm.count("help")) {
		std::cout << desc << std::endl;
		exit (0);
	}

	if (vm.count("port")) {
		_port = vm["port"].as<std::uint16_t>();
	}

	if (vm.count("bdd_filename")) {
		_bddFileName = vm["bdd_filename"].as<std::string>();
	}
}

}