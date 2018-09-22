/*
** EPITECH PROJECT, 2018
** babel
** File description:
** INetwork.hpp
*/

#pragma once

#include <functional>
#include <cinttypes>

namespace nw {

class ISocket {
protected:
	enum class Type {
		UDP,
		TCP
	};
public:
	ISocket(Type connectionType): _type(connectionType) {}

	virtual std::size_t	send(std::uint8_t *buff, std::size_t len) = 0;
	virtual std::size_t	receive(std::uint8_t *buff, std::size_t len) = 0;
	virtual std::size_t	available(void) const = 0;
protected:
	inline Type	getType(void) const { return _type; }

	Type	_type;
};

class ITCPSocket: ISocket {
public:
	ITCPSocket(): ISocket(Type::TCP) {}

	virtual void	connect(std::string const &host, std::uint16_t port) = 0;
};

}