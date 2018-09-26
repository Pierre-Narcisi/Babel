/*
** EPITECH PROJECT, 2018
** babel
** File description:
** test.cpp
*/

#include <cstring>

#include "Db.h"
#include "Protocol.h"

struct Client {
	std::string username;
	std::string password;

	static void serializer(Client const &client, db::Element &element, db::Db &db)
	{
		element["username"] = client.username;
		element["password"] = client.password;
		element["icon"] = "";
	}
	static Client deserializer(db::Element &element, db::Db &db)
	{
		return Client{
			.username = element["username"].as<std::string>(),
			.password = element["password"].as<std::string>(),
		};
	}
};

babel::protocol::Connect createPacketConnect(db::Db &db, std::string const &username, std::string const &password)
{
	babel::protocol::Connect packet;

	packet.type = babel::protocol::Packet::Type::Connect;
	std::strncpy(packet.username, username.c_str(), 128);
	std::strncpy(packet.password, password.c_str(), 128);
	return packet;
}

int main(int ac, char **av)
{
	if (ac != 3)
		return 1;
	db::Db db;

	db.importDb("bla.db");
	db.createTable("client", {
		{"username", db::Data::Type::String},
		{"password", db::Data::Type::String},
		{"icon", db::Data::Type::String}
	}, Client::serializer, Client::deserializer);

	if (db["client"].getAll().size() == 0) {
		db.insert(Client{"Jhon Doe", "toto42"});
	}

	babel::protocol::Sender sender{&db};

	babel::protocol::Connect connect = createPacketConnect(db, av[1], av[2]);
	sender.sendPacket(connect);

	db.exportDb("bla.db");
}