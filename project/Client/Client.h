/*
** EPITECH PROJECT, 2018
** ProjAudio
** File description:
** Client.h
*/

#pragma once

#include <string>
#include <vector>

#include "Common/Image.h"
#include "Common/Network.h"

#include "Friend.h"

namespace babel {

struct ClientInfo {
	std::string 		name;
	babel::Image		icon;
	std::vector<FriendInfo>	friends;
};

class Client {
public:

private:
	INetwork		&network;
	ClientInfo		info;
};

}