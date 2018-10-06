/*
** EPITECH PROJECT, 2018
** babel
** File description:
** ASocket.hpp
*/

#pragma once

#include "ISocket.hpp"

namespace nw {

class ASocket: public ISocket {
protected:
	enum class Type {
		UDP,
		TCP
	};
public:
	using Handler = std::function<int(std::size_t)>;
	
	ASocket(Type connectionType): _type(connectionType) {}
    void        setOnReadable(typename ASocket::Handler &&func);
	
protected:
	inline Type	_getType(void) const { return _type; }

	Handler		_hdl;
	Type		_type;
};

class ATCPSocket: public ASocket {
public:
	ATCPSocket(): ASocket(Type::TCP), _isConnected(false) {}
	virtual ~ATCPSocket() = 0;

	virtual void	connect(std::string const &host, std::uint16_t port) = 0;
	virtual void    disconnect(void) = 0;
	inline void     setOnDisconnect(std::function<void(void)> const &hdl) { _onDisconnect = hdl; }
protected:
	using		ASocket::_getType;
	using		ASocket::_hdl;
	std::function<void(void)>
			_onDisconnect;
	bool		_isConnected;
};

}
