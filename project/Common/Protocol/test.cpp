/*
** EPITECH PROJECT, 2018
** babel
** File description:
** test.cpp
*/

#include <cstring>

#include "Protocol.h"

babel::protocol::Connect createPacketConnect(db::Db &db, std::string const &username, std::string const &password)
{
	babel::protocol::Connect packet;

	packet.type = babel::protocol::Packet::Type::Connect;
	std::strncpy(packet.username, username.c_str(), 128);
	std::strncpy(packet.password, password.c_str(), 128);
	return packet;
}


void createDefaultDb(db::Db &db)
{
	db.createTable("client", {
		{"username", db::Data::Type::String},
		{"password", db::Data::Type::String},
		{"icon", db::Data::Type::String}
	}, babel::Client::serializer, babel::Client::deserializer);
	db.createTable("friend", {
		{"clientRef", db::Data::Type::Number},
		{"name", db::Data::Type::String},
	}, babel::Friend::serializer, babel::Friend::deserializer);
	db.createTable("friendListRef", {
		{"clientKey", db::Data::Type::Number},
		{"friendKey", db::Data::Type::Number}
	}, babel::FriendRef::serializer);

}

void defaultInstance(db::Db &db)
{
	babel::Client jhon{"Jhon Doe", "toto42", "oui.icon"};
	babel::Client jane{"Jane Doe", "Jane", "oui.icon"};
	babel::Client steeve{"Steeve Oui", "Steevoui", "steeve.icon"};
	db.insert(jhon);
	db.insert(steeve);
	db.insert(jane);
	jhon.newFriend("Jane Doe", db);
	jhon.newFriend("Steeve Oui", db);
}

int main(int ac, char **av)
{
	if (ac != 3)
		return 1;
	db::Db db;

	createDefaultDb(db);
	if (db.importDb("bla.db") == false)
		defaultInstance(db);

	babel::Client client;

	babel::protocol::ServerSender servSender{db};
	babel::protocol::ClientSender cliSender{client};

	babel::protocol::clitmp = &cliSender;
	babel::protocol::servtmp = &servSender;

	babel::protocol::Connect connect = createPacketConnect(db, av[1], av[2]);
	cliSender.sendPacket(connect);

	std::cout << client.username << ":\n";
	for (auto c : client.icon) {
		std::cout << c;
	}
	std::cout << std::endl;
	for (auto f : client.friends) {
		std::cout << f.username << "  " << f.state << std::endl;
	}

	db.exportDb("bla.db");
}