/*
** EPITECH PROJECT, 2018
** babel
** File description:
** Bdd.h
*/

#pragma once

#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <unordered_map>
#include <memory>

#include "BddData.h"

namespace bdd {

class Bdd {
/* à plusieurs Table. ex: bdd["sushi"] ou bdd["vehicule"] */
private:

	class Table {
	/* à plusieurs Element. ex: bdd["sushi"][0] ou bdd["vehicule"][1] */
	private:

		class Element {
		/* à plusieurs data. ex: bdd["sushi"][0]["riz"] ou bdd["vehicule"][0]["nb_roue"] */
		public:
			Element(std::unordered_map<std::string, Data::Type> &description);

			Data &operator[](std::string const &dataName);

			friend std::ostream &operator<<(std::ostream &os, Element const &element)
			{
				os << "{\n";
				bool first = true;
				for (auto const &e : element._datas) {
					if (first == false) {
						os << ",\n";
					} else {
						first = false;
					}
					switch (element._description[e.first]) {
						case Data::Type::Number:
							os << "    \"" << e.first << "\": " << e.second.to<Data::Number>();
							break;
						case Data::Type::Float:
							os << "    \"" << e.first << "\": " << e.second.to<Data::Float>();
							break;
						case Data::Type::String:
							os << "    \"" << e.first << "\": \"" << e.second.to<Data::String>() << "\"";
							break;
						// case Data::Type::Date:
						// 	os << "    \"" << e.first << "\": " << asctime(localtime(&e.second.to<Data::Date>()));
						// 	break;
					}
				}
				return os << "\n  }";
			}

		private:
			std::unordered_map<std::string, Data::Type>	&_description;
			std::unordered_map<std::string, Data>		_datas;
		}; /* class Element */

	public:
		Table(Bdd &bdd): _bdd{bdd} {}

		void setDescription(std::string const &dataName, Data::Type type);

		size_t newElement();

		Element &operator[](size_t key);

		friend std::ostream &operator<<(std::ostream &os, Table const &champ)
		{
			os << "{\n";
			bool first = true;
			for (auto i = 0; i < champ._elements.size(); ++i) {
				if (first == false) {
					os << ",\n";
				} else {
					first = false;
				}
				os << "  " << i << ": " << champ._elements[i];

			}
			return os << "\n}";
		}

	private:
		Bdd						&_bdd;
		std::unordered_map<std::string, Data::Type>	_description;
		std::vector<Element>				_elements;
	}; /* class Table */

public:

	void createTable(std::string const &tableName, std::vector<std::pair<std::string, Data::Type>> const & = {});

	Table &operator[](std::string const &tableName);

	friend std::ostream &operator<<(std::ostream &os, Bdd const &bdd);

private:
	std::unordered_map<std::string, Table>	_tables;
}; /* class Bdd */

} /* namespace bdd */