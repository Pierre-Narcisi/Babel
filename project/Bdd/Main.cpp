/*
** EPITECH PROJECT, 2018
** babel
** File description:
** Main.cpp
*/

#include "Bdd.h"

struct Sushi {
	std::string	repas;
	float		temps;
	long		riz;
	int		saumon;
};

void sushiSerializer(Sushi const &sushi, bdd::Element &element)
{
	element["repas"] = sushi.repas;
	element["temps"] = sushi.temps;
	element["riz"] = sushi.riz;
	element["saumon"] = sushi.saumon;
}

Sushi sushiDeserializer(bdd::Element &element)
{
	Sushi sushi;

	sushi.repas = element["repas"].to<bdd::Data::String>();
	sushi.temps = element["temps"].to<bdd::Data::Float>();
	sushi.riz = element["riz"].to<bdd::Data::Number>();
	sushi.saumon = element["saumon"].to<bdd::Data::Number>();

	return sushi;
}

int main()
{
	bdd::Bdd bdd;

	bdd.createTable("client", {
		{"nom", bdd::Data::Type::String},
		{"menuChoisi", bdd::Data::Type::Key}
	});
	bdd.createTable("menu", {
		{"nom", bdd::Data::Type::String}
	});
	bdd.createTable("sushi", {
		{"repas", bdd::Data::Type::String},
		{"temps", bdd::Data::Type::Float},
		{"riz", bdd::Data::Type::Number},
		{"saumon", bdd::Data::Type::Number}
	}, sushiSerializer, sushiDeserializer);

	Sushi sushi{"soir", 1, 2, 3};

	auto s1 = bdd.insert(sushi);

	auto e1 = bdd["sushi"].newElement();
	bdd["sushi"][e1]["riz"] = 42;
	bdd["sushi"][e1]["saumon"] = 12;

	bdd.insert(Sushi{"midi", 30.5, 42, 12});

	Sushi sushi2 = bdd["sushi"].get<Sushi>(s1);

	if (sushi.repas != sushi2.repas || sushi.temps != sushi2.temps || sushi.riz != sushi2.riz || sushi.saumon != sushi2.saumon)
		std::cerr << "error deserialization" << std::endl;
	else
		std::cerr << "good deserialization" << std::endl;

	auto idmenu1 = bdd["menu"].newElement();
	bdd["menu"][idmenu1]["nom"] = "12 sushi";


	auto idclient1 = bdd["client"].newElement();
	bdd["client"][idclient1]["nom"] = "Jean";
	bdd["client"][idclient1]["menuChoisi"] = bdd["menu"][idmenu1].getKey();

	std::cout << bdd;
}