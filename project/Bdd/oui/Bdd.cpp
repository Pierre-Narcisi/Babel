/*
** EPITECH PROJECT, 2018
** babel
** File description:
** Bdd.tpp
*/

#include "Bdd.h"

namespace bdd {

Bdd::Table &Bdd::operator[](std::string const &champ_name)
{
	if (_champs.find(champ_name) == _champs.end()) {
		_champs.emplace(champ_name, Table{*this});
	}
	return _champs.at(champ_name);
}

std::ostream &operator<<(std::ostream &os, Bdd const &bdd)
{
	for (auto const &e : bdd._champs) {
		os << "\"" << e.first << "\": " << e.second << "\n";
	}
	return os;
}

void Bdd::Table::setDescription(std::string const &data_name, Data::Type type)
{
	if (_description.find(data_name) != _description.end()) {
		throw std::runtime_error{"DataType already set"};
	}
	_description[data_name] = type;
}

size_t Bdd::Table::newElement()
{
	_elements.push_back({_description});
	return _elements.size() - 1;
}


Bdd::Table::Element &Bdd::Table::operator[](size_t key)
{
	return _elements.at(key);
}

// std::ostream &operator<<(std::ostream &os, Bdd::Table const &champ)
// {
// 	os << "{\n";
// 	bool first = true;
// 	for (auto i = 0; i < champ._elements.size(); ++i) {
// 		if (first == false) {
// 			os << ",\n";
// 		} else {
// 			first = false;
// 		}
// 		os << "  " << i << ": " << champ._elements[i];

// 	}
// 	return os << "\n}";
// }

Bdd::Table::Element::Element(std::unordered_map<std::string, Data::Type> &description):
_description{description}
{}

Data	&Bdd::Table::Element::operator[](std::string const &data_name)
{
	if (_description.find(data_name) == _description.end()) {
		throw std::runtime_error{"get data : bad name of data"};
	}
	if (_datas.find(data_name) == _datas.end()) {
		_datas.emplace(data_name, _description.at(data_name));
	}
	return _datas.at(data_name);
}

}