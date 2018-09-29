/*
** EPITECH PROJECT, 2018
** babel
** File description:
** QtSocket.hpp
*/

#pragma once

#include <QTcpSocket>
#include <QString>
#include <exception>
#include "ISocket.hpp"

namespace nw {
namespace qt {

class TCPSocket : public ATCPSocket {
public:
	TCPSocket(QObject *parent);

	virtual std::size_t	send(std::uint8_t *buff, std::size_t len) final;
	virtual std::size_t	receive(std::uint8_t *buff, std::size_t len) final;
	virtual std::size_t	available(void) const final;
	virtual void		connect(std::string const &host, std::uint16_t port) final;
private:
	QTcpSocket	_socket;
};

}
}
