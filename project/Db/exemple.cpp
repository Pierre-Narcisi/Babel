/*
** EPITECH PROJECT, 2018
** babel
** File description:
** Main.cpp
*/

#include <assert.h>

#include "Db.h"

struct Sushi {
	std::string	repas;
	float		temps;
	long		riz;
	int		saumon;

	static void serializer(Sushi const &sushi, db::Element &element, db::Db &db)
	{
		element["repas"] = sushi.repas;
		element["temps"] = sushi.temps;
		element["riz"] = sushi.riz;
		element["saumon"] = sushi.saumon;
	}
	static Sushi deserializer(db::Element &element, db::Db &db)
	{
		return Sushi{
			.repas = element["repas"].to<std::string>(),
			.temps = element["temps"].to<float>(),
			.riz = element["riz"].to<long>(),
			.saumon = element["saumon"].to<int>()
		};
	}
};

struct Menu {
	std::string name;

	static void serializer(Menu const &menu, db::Element &element, db::Db &db)
	{
		element["name"] = menu.name;
	}
	static Menu deserializer(db::Element &element, db::Db &db)
	{
		return Menu{element["name"].to<std::string>()};
	}
};

struct Client {
	std::string name;
	Menu menu;

	static void serializer(Client const &client, db::Element &element, db::Db &db)
	{
		element["name"] = client.name;
		element["menuChoisi"] = db.insert(client.menu);
	}
	static Client deserializer(db::Element &element, db::Db &db)
	{
		return Client{
			.name = element["name"].to<std::string>(),
			.menu = db.get<Menu>(element["menuChoisi"].to<db::Key>())
		};
	}
	static void remover(db::Element &element, db::Db &db)
	{
		db["menu"].remove(element["menuChoisi"].to<db::Key>());
	}
};

int main()
{
	db::Db db;

	db.createTable("client", {
		{"name", db::Data::Type::String},
		{"menuChoisi", db::Data::Type::Number}
	}, Client::serializer, Client::deserializer, Client::remover);
	db.createTable("menu", {
		{"name", db::Data::Type::String}
	}, Menu::serializer, Menu::deserializer);
	db.createTable("sushi", {
		{"repas", db::Data::Type::String},
		{"temps", db::Data::Type::Float},
		{"riz", db::Data::Type::Number},
		{"saumon", db::Data::Type::Number}
	}, Sushi::serializer, Sushi::deserializer);

	/* test de serialisation/deserialisation simple */
	Sushi sushi{"soir", 1, 2, 3};

	auto keySushi1 = db.insert(sushi);
	auto keySushi2 = db["sushi"].newElement();
	db["sushi"][keySushi2]["riz"] = 42;
	db["sushi"][keySushi2]["saumon"] = 12;
	db.insert(Sushi{"midi", 30.5, 42, 12});
	Sushi sushi2 = db["sushi"].get<Sushi>(keySushi1);

	assert(sushi.repas == sushi2.repas && sushi.temps == sushi2.temps && sushi.riz == sushi2.riz && sushi.saumon == sushi2.saumon);

	/* test de la multi serialisation/deserialisation */
	Client client1{"Jean", {"12 sushi"}};

	auto keyClient1 = db.insert(client1);
	Client client2 = db.get<Client>(keyClient1);
	assert(client1.name == client2.name && client1.menu.name == client2.menu.name);

	std::cout << db;

	db::Array arr = db["sushi"].getAll().where([](db::Element const &e){return e["saumon"].to<int>() == 12;});

	assert(arr.size() == 2);

	db["sushi"].remove(keySushi2);
	db["client"].remove(keyClient1);
	
	std::cout << "---------------------------" << std::endl;
	std::cout << db;

}