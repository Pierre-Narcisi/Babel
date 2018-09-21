/*
** EPITECH PROJECT, 2018
** babel
** File description:
** QtSocket.hpp
*/

#pragma once

#include <QTcpSocket>
#include <QString>
#include "INetwork.hpp"

namespace nw {
namespace qt {

class TCPSocket {
public:
	TCPSocket(QObject *parent);

	virtual std::size_t	send(std::uint8_t *buff, std::size_t len) final;
	virtual std::size_t	receive(std::uint8_t *buff, std::size_t len) final;
	virtual std::size_t	available(void) const final;
	virtual void		connect(std::string const &host, std::uint16_t port) final;
private:
	QTcpSocket	_socket;
};

TCPSocket::TCPSocket(QObject *parent):
	_socket(parent) {}

void	TCPSocket::connect(std::string const &host, std::uint16_t port) {
	_socket.connectToHost(QString::fromStdString(host), port);
	if (_socket.waitForConnected()) {
		std::cout << "connected" << std::endl;
	} else {
		std::cout << "failed to connect:" <<
		_socket.errorString().toStdString() << std::endl;
	}
}

std::size_t	TCPSocket::send(std::uint8_t *buff, std::size_t len) {
	auto	wlen = _socket.write((char*) buff, len);

	_socket.waitForBytesWritten();
	return wlen;
}

std::size_t	TCPSocket::receive(std::uint8_t *buff, std::size_t len) {

	auto	wlen = _socket.read((char*) buff, len);

	return (wlen);
}

std::size_t	TCPSocket::available(void) const {
	return _socket.bytesAvailable();
}

}
}