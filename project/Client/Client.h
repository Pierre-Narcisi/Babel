/*
** EPITECH PROJECT, 2018
** ProjAudio
** File description:
** Client.h
*/

#pragma once

#include <string>
#include <vector>
#include <memory>

#include "Common/Image.h"
#include "Common/Network/INetwork.hpp"

#include "Friend.h"

namespace babel {

class Client {
public:

private:
	std::shared_ptr<ISocket>	socket; /* the socket interface */
	std::string			name; /* your name */
	babel::Image			icon; /* your icon */
	std::vector<Friend>		friends; /* your friend list */
	// missing :
	// tcp socket
	// bool inCall;
	// std::size_t calledFriend;
};

}