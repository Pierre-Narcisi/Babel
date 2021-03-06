/*
** EPITECH PROJECT, 2018
** babel
** File description:
** QtSocket.cpp
*/

#include "QtSocket.hpp"

namespace nw {
namespace qt {

TCPSocket::TCPSocket(QObject *parent):
        _socket(parent) {
    QObject::connect(&_socket, &QTcpSocket::readyRead, [this] {
        std::size_t len;
        while ((len = _socket.bytesAvailable())) {
            _hdl.operator()(len);
        }
    });

    QObject::connect(&_socket, &QTcpSocket::disconnected, [this] {
        if (_isConnected) {
            this->_isConnected = false;
            this->_onDisconnect();
        }
    });
}

TCPSocket::~TCPSocket() {
    disconnect();
}

void	TCPSocket::connect(std::string const &host, std::uint16_t port) {
	_socket.connectToHost(QString::fromStdString(host), port);
    if (_socket.waitForConnected(5000)) {
        this->_isConnected = true;
		return;
	} else {
		throw std::runtime_error((std::string("failed to connect: ") +
			_socket.errorString().toStdString()).c_str());
	}
}

void TCPSocket::disconnect(void) {
    _isConnected = false;
    _socket.close();
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
