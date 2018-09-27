/*
** EPITECH PROJECT, 2018
** babel
** File description:
** BabelStruct.cpp
*/

#include "BabelStruct.h"

namespace babel {

db::Key Client::newFriend(std::string const &friendName, db::Db &db)
{
	auto me = db["client"].getAll().where([this](db::Element const &e){
		return e["username"].as<std::string>() == username;
	});
	auto you = db["client"].getAll().where([&friendName](db::Element const &e){
		return e["username"].as<std::string>() == friendName;
	});
	auto mf = you.back();
	Friend myfriend;
	myfriend.username = mf["username"].as<std::string>();
	myfriend.iconfile = mf["icon"].as<std::string>();
	myfriend.name = mf["username"].as<std::string>();
	auto yourKey = db.insert(myfriend);

	Friend reverseFriend;
	myfriend.username = username;
	myfriend.iconfile = iconfile;
	myfriend.name = username;
	auto myKey = db.insert(myfriend);

	db.insert(FriendRef{me.back()["primary_key"].as<db::Key>(), yourKey});
	db.insert(FriendRef{you.back()["primary_key"].as<db::Key>(), myKey});
	return yourKey;
}

void Client::serializer(Client const &client, db::Element &element, db::Db &db)
{
	element["username"] = client.username;
	element["password"] = client.password;
	element["icon"] = client.iconfile;
}

Client Client::deserializer(db::Element &element, db::Db &db)
{
	return Client{
		.username = element["username"].as<std::string>(),
		.password = element["password"].as<std::string>(),
		.iconfile = element["icon"].as<std::string>(),
		.key = element["primary_key"].as<db::Key>()
	};
}

void Friend::serializer(Friend const &myfriend, db::Element &element, db::Db &db)
{
	auto elems = db["client"].getAll().where([&myfriend](db::Element const &e){
		return e["username"].as<std::string>() == myfriend.username;
	});
	if (elems.size() == 0)
		return;
	element["clientRef"] = elems.back()["primary_key"];
	element["name"] = myfriend.name;
}

Friend Friend::deserializer(db::Element &element, db::Db &db)
{
	auto client = db["client"].get<Client>(element["clientRef"].as<db::Key>());
	Friend f;
	f.state = false;
	f.username = client.username;
	f.name = element["name"].as<std::string>();
	f.iconfile = client.iconfile;
	return f;
}

void FriendRef::serializer(FriendRef const &ref, db::Element &elem, db::Db &db)
{
	elem["clientKey"] = ref.clientKey;
	elem["friendKey"] = ref.friendKey;
}


}
