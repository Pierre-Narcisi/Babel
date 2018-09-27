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
#include "Db/Db.h"

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
	std::list<::boost::shared_ptr<Client>>	_clts; /* list all connected clients */
	db::Db					_db; /* store all data of clients, their friends and their conversations */
};

class CoreServer::CoreArgs {
public:
	CoreArgs(int ac, char **av);

	inline std::uint16_t		port(void) const { return _port; }
	inline const std::string	dbFileName(void) const { return _dbFileName; }
private:
	std::uint16_t	_port;
	std::string	_dbFileName;
};

}