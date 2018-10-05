/*
** EPITECH PROJECT, 2018
** babel
** File description:
** Db.tpp
*/

#include <algorithm>
#include <sstream>
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

void Db::exportDb(std::string const &filename) const
{
	std::ofstream file{filename};

	if (file.fail()) {
		std::cerr << "Fail to open file " << filename << std::endl;
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
	auto elemIt = std::find_if(_elements.begin(), _elements.end(), [key](Element &e){return e["primary_key"].as<Key>() == key;});
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
			remove(e["primary_key"].as<Key>());
		}
	}
}

Key Table::newElement()
{
	_elements.push_back(Element{*this});
	_elements.back()["primary_key"] = _lastElementKey;
	++_lastElementKey;
	return _lastElementKey - 1;
}

Element &Table::operator[](Key key)
{
	auto elemIt = std::find_if(_elements.begin(), _elements.end(), [key](Element &e){return e["primary_key"].as<Key>() == key;});
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
	os << '{' << element["primary_key"].as<std::size_t>();
	for (auto e : element._table.getDescription()) {
		if (e.first != "primary_key") {
			os << ";";
			if (element._datas.find(e.first) != element._datas.end()) {
				switch (e.second) {
					case Data::Type::Number:
						os << element[e.first].as<Data::Number>();
						break;
					case Data::Type::Float:
						os << element[e.first].as<Data::Float>();
						break;
					case Data::Type::String:
						os << '\"' << element[e.first].as<Data::String>() << '\"';
						break;
				}
			}
		}
	}
	return os << "}\n";
}


bool Db::importDb(std::string const &filename)
{
	std::ifstream file{filename};

	if (file.fail()) {
		std::cerr << "fail to open file " << filename << std::endl;
		return false;
	}
	std::string str;

	while (std::getline(file, str)) {
		std::stringstream sstr{str};
		std::string tableName;
		char sep;
		std::size_t lastKey, elementNumber;

		std::getline(sstr, str, ':');
		sstr >> lastKey >> sep >> elementNumber;

		if (str.find('\"') == str.rfind('\"') || sstr.fail() || sep != ':') {
			std::cerr << "error pars" << std::endl;
			return false;
		}
		str = str.substr( + 1);
		tableName = str.substr(0, str.rfind('\"'));
		_tables.emplace(tableName, Table{*this, tableName});

		if (_tables.at(tableName).importTable(file, lastKey, elementNumber) == false) {
			std::cerr << "error pars" << std::endl;
		}
	}
	return true;
}

bool Table::importTable(std::ifstream &file, std::size_t lastKey, std::size_t nbElement)
{
	std::string str;
	std::getline(file, str);
	if (str.length() == 0 || str[0] != '{' || str[str.length() - 1] != '}') {
		return false;
	}

	std::stringstream sstr{str.substr(1, str.length() - 2)};
	std::vector<std::string> dataNames;

	while (std::getline(sstr, str, ':')) {
		std::string str_;
		while (std::count(str.begin(), str.end(), '\"') != 2 && std::getline(sstr, str_, ':'))
			str += str_;
		if (str.length() == 0 || str[0] != '\"' || str[str.length() - 1] != '\"') {
			return false;
		}
		dataNames.push_back(str.substr(1, str.length() - 2));
		std::getline(sstr, str, ';');
		if (str == "Number") {
			setDescription(dataNames.back(), Data::Type::Number);
		} else if (str == "Float") {
			setDescription(dataNames.back(), Data::Type::Float);
		} else if (str == "String") {
			setDescription(dataNames.back(), Data::Type::String);
		} else {
			return false;
		}
	}
	setDescription("primary_key", Data::Type::Number);
	
	/* pars all line */
	_lastElementKey = lastKey;
	for (auto i = 0; i < nbElement; ++i) {
		std::getline(file, str);
		if (file.fail() || str.length() == 0
		|| str[0] != '{' || str[str.length() - 1] != '}'
		|| std::count(str.begin(), str.end(), ';') != dataNames.size())
			return false;
		std::stringstream sstr{str.substr(1, str.length() - 2)};
		Key key;
		Key firstKey = newElement();

		for (auto i = 0; i < dataNames.size() + 1; ++i) {
			if (i == 0) {
				sstr >> key;
				char c;
				sstr >> c;
				(*this)[firstKey]["primary_key"] = key;
			} else {
				if (_description[dataNames[i - 1]] == Data::Type::Number) {
					
					Data::Number number = 0;
					sstr >> number;
					(*this)[key][dataNames[i - 1]] = number;
					char c;
					sstr >> c;
				} else if (_description[dataNames[i - 1]] == Data::Type::Float) {
					Data::Float f = 0;
					sstr >> f;
					(*this)[key][dataNames[i - 1]] = f;
					char c;
					sstr >> c;
				} else {
					Data::String s;
					std::getline(sstr, s, ';');
					if (s.length() == 0 || s[0] != '\"' || s[s.length() - 1] != '\"') {
						return false;
					}
					(*this)[key][dataNames[i - 1]] = s.substr(1, s.length() - 2);
				}
			}
		}
	}
	_lastElementKey = lastKey;
	return true;
}

}