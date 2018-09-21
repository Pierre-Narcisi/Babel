/*
** EPITECH PROJECT, 2018
** babel
** File description:
** Main.cpp
*/

#include "Bdd.h"

int main()
{
	bdd::Bdd bdd;

	bdd.createTable("sushi", {
		{"repas", bdd::Data::Type::String},
		{"temps", bdd::Data::Type::Float},
		{"riz", bdd::Data::Type::Number},
		{"saumon", bdd::Data::Type::Number}
	});

	auto e1 = bdd["sushi"].newElement();
	auto e2 = bdd["sushi"].newElement();
	bdd["sushi"][e1]["riz"] = 42;
	bdd["sushi"][e1]["saumon"] = 12;
	bdd["sushi"][e2]["riz"] = 42;
	bdd["sushi"][e2]["saumon"] = 12;
	bdd["sushi"][e2]["repas"] = "midi";
	bdd["sushi"][e2]["temps"] = 30.5;

	std::cout << bdd;
}