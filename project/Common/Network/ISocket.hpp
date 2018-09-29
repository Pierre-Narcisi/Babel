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
public:
	ISocket() = default;

	virtual std::size_t	send(std::uint8_t *buff, std::size_t len) = 0;
	virtual std::size_t	receive(std::uint8_t *buff, std::size_t len) = 0;
	virtual std::size_t	available(void) const = 0;
};

class ASocket: public ISocket {
protected:
	enum class Type {
		UDP,
		TCP
	};
public:
	using Handler = std::function<int(std::size_t)>;
	
	ASocket(Type connectionType): _type(connectionType) {}
	inline std::function<void()>
				addHandlerOnReadable(typename ASocket::Handler &&func);
	
protected:
	inline Type	_getType(void) const { return _type; }

	std::list<Handler>	_hdls;
	Type			_type;
};

class ATCPSocket: public ASocket {
public:
	ATCPSocket(): ASocket(Type::TCP) {}

	virtual void	connect(std::string const &host, std::uint16_t port) = 0;
	inline void	setOnDisconnect(std::function<void(void)> const &hdl) { _onDisconnect = hdl; }
protected:
	using		ASocket::_getType;
	using		ASocket::_hdls;
	std::function<void(void)>
			_onDisconnect;
};

std::function<void()>
ASocket::addHandlerOnReadable(Handler &&func) {
	auto	it = _hdls.insert(_hdls.end(), func);

	return [this, it] {
		_hdls.erase(it);
	};
}
}