/*
** EPITECH PROJECT, 2018
** babel
** File description:
** Friend.h
*/

#pragma once

#include <string>
#include <vector>
#include <ctime>

#include "Common/Image.h"

namespace babel {

struct Message {
	std::string	name;
	std::string	message;
	std::time_t	time;
};

struct Friend {
	bool			state; // connected
	std::string		name;
	std::string		username;
	Image			icon;
	std::vector<Message>	messages;
};

}