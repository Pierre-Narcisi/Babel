/*
** EPITECH PROJECT, 2018
** babel
** File description:
** Bdd.tpp
*/

#include "Bdd.h"

namespace bdd {

void Bdd::createTable(std::string const &tableName, std::vector<std::pair<std::string, Data::Type>> const &descriptions)
{
	_tables.emplace(tableName, Table{*this});
	for (auto e : descriptions) {
		_tables.at(tableName).setDescription(e.first, e.second);
	}
}

Bdd::Table &Bdd::operator[](std::string const &tableName)
{
	if (_tables.find(tableName) == _tables.end()) {
		throw std::runtime_error{"error : table \"" + tableName + "\" not found"};
	}
	return _tables.at(tableName);
}

std::ostream &operator<<(std::ostream &os, Bdd const &bdd)
{
	for (auto const &e : bdd._tables) {
		os << "\"" << e.first << "\": " << e.second << "\n";
	}
	return os;
}

void Bdd::Table::setDescription(std::string const &dataName, Data::Type type)
{
	if (_description.find(dataName) != _description.end() && _description.at(dataName) != type) {
		throw std::runtime_error{"DataType already set"};
	}
	_description[dataName] = type;
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

Bdd::Table::Element::Element(std::unordered_map<std::string, Data::Type> &description):
_description{description}
{}

Data	&Bdd::Table::Element::operator[](std::string const &dataName)
{
	if (_description.find(dataName) == _description.end()) {
		throw std::runtime_error{"get data : data \"" + dataName + "\" not found"};
	}
	if (_datas.find(dataName) == _datas.end()) {
		_datas.emplace(dataName, _description.at(dataName));
	}
	return _datas.at(dataName);
}

}