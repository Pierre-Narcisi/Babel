/*
** EPITECH PROJECT, 2018
** babel
** File description:
** TmpStruct.h
*/

#pragma once

#include <string>

#include "Db.h"

namespace babel {

struct Client;
struct Friend;

struct Client {
	std::string		username;
	std::string		password;
	std::string		iconfile;
	std::vector<char>	icon;
	std::vector<Friend>	friends;
	db::Key			key = -1;

	db::Key newFriend(std::string const &friendName, db::Db &db);

	static void serializer(Client const &client, db::Element &element, db::Db &db);
	static Client deserializer(db::Element &element, db::Db &db);
};

struct Friend {
	bool			state;
	std::string		username;
	std::string		name;
	std::string		iconfile;
	std::vector<char>	icon;

	static void serializer(Friend const &myfriend, db::Element &element, db::Db &db);
	static Friend deserializer(db::Element &element, db::Db &db);
};

struct FriendRef {
	db::Key clientKey;
	db::Key friendKey;

	static void serializer(FriendRef const &pair, db::Element &elem, db::Db &db);
};

}