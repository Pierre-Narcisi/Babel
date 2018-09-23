/*
** EPITECH PROJECT, 2018
** babel
** File description:
** CoreServer.hpp
*/

#pragma once

#include <list>
#include <memory>
#include "boost/asio.hpp"
#include "Client/Client.hpp"

namespace srv {

class CoreServer {
public:
	explicit CoreServer(int ac, char **av);
	
	void	start(void);
private:
	class CoreArgs;

	void	_startAccept(void);
	void	_handleAccept(Client::ptr newClient, const ::boost::system::error_code& error);

	std::unique_ptr<CoreArgs>		_args;
	::boost::asio::io_service		_ios;
	::boost::asio::ip::tcp::acceptor	_acceptor;
	std::list<::boost::shared_ptr<Client>>	_clts;
};

class CoreServer::CoreArgs {
public:
	CoreArgs(int ac, char **av);

	inline std::uint16_t		port(void) const { return _port; }
	inline const std::string	bddFileName(void) const { return _bddFileName; }
private:
	std::uint16_t	_port = 5555;
	std::string	_bddFileName = ".bdd";
};

}