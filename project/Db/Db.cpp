/*
** EPITECH PROJECT, 2018
** babel
** File description:
** Db.tpp
*/

#include <algorithm>

#include <fstream>

#include "Db.h"

namespace db {

Array Array::where(std::function<bool (Element const &)> const &func) const
{
	Array arr;

	for (auto e : *this) {
		if (func(e) == true) {
			arr.push_back(e);
		}
	}
	return arr;
}

Table &Db::operator[](std::string const &tableName)
{
	if (_tables.find(tableName) == _tables.end()) {
		throw std::runtime_error{"error : table \"" + tableName + "\" not found"};
	}
	return _tables.at(tableName);
}

void Db::importDb(std::string const &filename)
{
}

void Db::exportDb(std::string const &filename) const
{
	std::ofstream file{filename};

	if (file.fail()) {
		std::cerr << "Fail to open filename";
	} else {
		file << *this;
	}
}

std::ostream &operator<<(std::ostream &os, Db const &db)
{
	for (auto e : db._tables) {
		os << e.second;
	}
	return os;
}

void Table::setDescription(std::string const &dataName, Data::Type type)
{
	if (_description.find(dataName) != _description.end() && _description.at(dataName) != type) {
		throw std::runtime_error{"DataType already set"};
	}
	_description[dataName] = type;
}

Array &Table::getAll()
{
	return _elements;
}

std::unordered_map<std::string, Data::Type> const &Table::getDescription() const
{
	return _description;
}

void Table::setRemover(remover_t remover)
{
	_remover = remover;
}

void Table::remove(Key key)
{
	auto elemIt = std::find_if(_elements.begin(), _elements.end(), [key](Element &e){return e["primary_key"].to<Key>() == key;});
	if (elemIt == _elements.end()) {
		throw std::runtime_error{"error : elememt " + std::to_string(key) + " does not exist"};
	}
	if (_remover)
		_remover(*elemIt, _db);
	_elements.erase(elemIt);
}

void Table::remove_if(std::function<bool (Element const &)> const &func)
{
	for (auto e : _elements) {
		if (func(e) == true) {
			remove(e["primary_key"].to<Key>());
		}
	}
}

Key Table::newElement()
{
	_elements.push_back(Element{*this});
	_elements.back()["primary_key"] = _lastElementKey;
	++_lastElementKey;
	return _elements.size() - 1;
}

Element &Table::operator[](Key key)
{
	auto elemIt = std::find_if(_elements.begin(), _elements.end(), [key](Element &e){return e["primary_key"].to<Key>() == key;});
	if (elemIt == _elements.end()) {
		throw std::runtime_error{"error : elememt " + std::to_string(key) + " does not exist"};
	}
	return *elemIt;
}

std::ostream &operator<<(std::ostream &os, Table const &table)
{
	os << '\"' << table._name << "\":" << table._lastElementKey << ':' << table._elements.size() << '\n';
	
	bool first = true;
	os << '{';
	for (auto e : table._description) {
		if (e.first != "primary_key") {
			if (first == false)
				os << ";";
			else
				first = false;
			os << '\"' << e.first << "\":";
			switch (e.second) {
				case Data::Type::Number:
					os << "Number";
					break;
				case Data::Type::Float:
					os << "Float";
					break;
				case Data::Type::String:
					os << "String";
					break;
			}
		}
	}
	os << "}\n";
	for (auto e : table._elements)
		os << e;
	return os;
}


Element::Element(Table &table):
_table{table}
{}

Data	&Element::operator[](std::string const &dataName)
{
	auto description = _table.getDescription();
	if (description.find(dataName) == description.end()) {
		throw std::runtime_error{"get data : data \"" + dataName + "\" not found"};
	}
	if (_datas.find(dataName) == _datas.end()) {
		_datas.emplace(dataName, description.at(dataName));
	}
	return _datas.at(dataName);
}

Data const &Element::operator[](std::string const &dataName) const
{
	auto description = _table.getDescription();
	if (_datas.find(dataName) == _datas.end()) {
		throw std::runtime_error{"get data : data \"" + dataName + "\" not found"};
	}
	return _datas.at(dataName);
}

std::ostream &operator<<(std::ostream &os, Element const &element)
{
	os << '{' << element["primary_key"].to<std::size_t>();
	for (auto e : element._table.getDescription()) {
		if (e.first != "primary_key") {
			os << ";";
			if (element._datas.find(e.first) != element._datas.end()) {
				switch (e.second) {
					case Data::Type::Number:
						os << element[e.first].to<Data::Number>();
						break;
					case Data::Type::Float:
						os << element[e.first].to<Data::Float>();
						break;
					case Data::Type::String:
						os << '\"' << element[e.first].to<Data::String>() << '\"';
						break;
				}
			}
		}
	}
	return os << "}\n";
}


}