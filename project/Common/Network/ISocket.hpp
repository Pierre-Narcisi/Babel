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

}
