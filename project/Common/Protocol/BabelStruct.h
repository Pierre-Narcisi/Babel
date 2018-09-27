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

struct Client {
	std::string username;
	std::string password;
	std::string iconfile;
	std::vector<char> icon;

	static void serializer(Client const &client, db::Element &element, db::Db &db)
	{
		element["username"] = client.username;
		element["password"] = client.password;
		element["icon"] = client.iconfile;
	}
	static Client deserializer(db::Element &element, db::Db &db)
	{
		return Client{
			.username = element["username"].as<std::string>(),
			.password = element["password"].as<std::string>(),
			.iconfile = element["icon"].as<std::string>()
		};
	}
};

}