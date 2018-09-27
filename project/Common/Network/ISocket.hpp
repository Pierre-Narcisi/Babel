/*
** EPITECH PROJECT, 2018
** babel
** File description:
** INetwork.hpp
*/

#pragma once

#include <functional>
#include <cinttypes>
#include <memory>
#include <list>

namespace nw {

class ISocket {
protected:
	enum class Type {
		UDP,
		TCP
	};
public:
	using Handler = std::function<int(std::size_t)>;
	
	ISocket(Type connectionType): _type(connectionType) {}

	virtual std::size_t	send(std::uint8_t *buff, std::size_t len) = 0;
	virtual std::size_t	receive(std::uint8_t *buff, std::size_t len) = 0;
	virtual std::size_t	available(void) const = 0;
	inline std::function<void()>
				addHandlerOnReadable(typename ::nw::ISocket::Handler &&func);
	
	std::list<Handler>	_hdls;
protected:
	inline Type	_getType(void) const { return _type; }

	Type			_type;
};

std::function<void()>
ISocket::addHandlerOnReadable(Handler &&func) {
	auto	it = _hdls.insert(_hdls.end(), func);

	return [this, it] {
		_hdls.erase(it);
	};
}

class ITCPSocket: public ISocket {
public:
	ITCPSocket(): ISocket(Type::TCP) {}

	virtual void	connect(std::string const &host, std::uint16_t port) = 0;
protected:
	Type			_type;
};

}