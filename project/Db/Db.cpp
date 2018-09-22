/*
** EPITECH PROJECT, 2018
** babel
** File description:
** Db.tpp
*/

#include "Db.h"

namespace db {

Table &Db::operator[](std::string const &tableName)
{
	if (_tables.find(tableName) == _tables.end()) {
		throw std::runtime_error{"error : table \"" + tableName + "\" not found"};
	}
	return _tables.at(tableName);
}

std::ostream &operator<<(std::ostream &os, Db const &db)
{
	for (auto const &e : db._tables) {
		os << "\"" << e.first << "\": " << e.second << "\n";
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

std::unordered_map<std::string, Data::Type> const &Table::getDescription() const
{
	return _description;
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
	return _elements.at(key);
}

std::ostream &operator<<(std::ostream &os, Table const &champ)
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

std::ostream &operator<<(std::ostream &os, Element const &element)
{
	os << "{\n";
	bool first = true;
	for (auto const &e : element._datas) {
		if (first == false) {
			os << ",\n";
		} else {
			first = false;
		}
		switch (element._table.getDescription().at(e.first)) {
			case Data::Type::Number:
				os << "    \"" << e.first << "\": " << e.second.to<Data::Number>();
				break;
			case Data::Type::Float:
				os << "    \"" << e.first << "\": " << e.second.to<Data::Float>();
				break;
			case Data::Type::String:
				os << "    \"" << e.first << "\": \"" << e.second.to<Data::String>() << "\"";
				break;
		}
	}
	return os << "\n  }";
}


}