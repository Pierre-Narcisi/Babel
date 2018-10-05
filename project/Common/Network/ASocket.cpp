/*
** EPITECH PROJECT, 2018
** babel
** File description:
** ASocket.cpp
*/

#include "ASocket.hpp"

namespace nw {

ATCPSocket::~ATCPSocket() {}

void	ASocket::setOnReadable(Handler &&func) {
	_hdl = func;
}

}