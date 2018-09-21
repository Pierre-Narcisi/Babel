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

class Bdd;
class Table;
class Element;


template<typename T>
using serializer_t = void (*)(T const &, Element &);
template<typename T>
using deserializer_t = T (*)(Element &);

class Table {
/* à plusieurs Element. ex: bdd["sushi"][0] ou bdd["vehicule"][1] */
public:
	Table(Bdd &bdd, std::string const &name): _bdd{bdd}, _name{name} {}

	void setDescription(std::string const &dataName, Data::Type type);

	template<typename T>
	void setSerializer(serializer_t<T> serializer);

	template<typename T>
	void setDeserializer(deserializer_t<T> deserializer);

	template<typename T>
	T get(size_t key);

	std::unordered_map<std::string, Data::Type> const &getDescription() const;

	size_t newElement();

	Element &operator[](size_t key);

	friend std::ostream &operator<<(std::ostream &os, Table const &champ);

private:
	Bdd						&_bdd;
	std::string					_name;
	std::unordered_map<std::string, Data::Type>	_description;
	std::vector<Element>				_elements;
	std::size_t					_lastElementKey = 0;
}; /* class Table */


class Bdd {
/* à plusieurs Table. ex: bdd["sushi"] ou bdd["vehicule"] */
public:
	using Key = std::size_t;
	template<typename T>
	using serializerFunc = Key (*)(T &&);

public:

	// void createTable(std::string const &tableName, std::vector<std::pair<std::string, Data::Type>> const & = {});
	template<typename T = void *, typename U = void *>
	void createTable(
		std::string const &tableName,
		std::vector<std::pair<std::string, Data::Type>> const &descriptions,
		serializer_t<T> serializer = nullptr,
		deserializer_t<U> deserializer = nullptr);


	template<typename T>
	void setSerializer(serializer_t<T> serializer, std::string const &tableName);
	template<typename T>
	void setDeserializer(deserializer_t<T> deserializer, std::string const &tableName);

	template<typename T>
	T get(Key key)
	{
		std::pair<std::string, void *> deserializerInfo = _deserializers[typeid(T).name()];
		return reinterpret_cast<deserializer_t<T>>(deserializerInfo.second)(_tables.at(deserializerInfo.first)[key]);
	}

	template<typename T>
	Bdd::Key insert(T const &);

	Table &operator[](std::string const &tableName);

	friend std::ostream &operator<<(std::ostream &os, Bdd const &bdd);

private:
	std::unordered_map<std::string, Table>		_tables;
	std::unordered_map<std::string, std::pair<std::string, void * /*aka serializer_t*/>>	_serializers;
	std::unordered_map<std::string, std::pair<std::string, void * /*aka deserializer_t*/>>	_deserializers;
}; /* class Bdd */


class Element {
/* à plusieurs data. ex: bdd["sushi"][0]["riz"] ou bdd["vehicule"][0]["nb_roue"] */
public:
	Element(Table &table);

	Data::Key getKey();

	Data &operator[](std::string const &dataName);

	friend std::ostream &operator<<(std::ostream &os, Element const &element);

private:
	Table						&_table;
	std::unordered_map<std::string, Data>		_datas;
}; /* class Element */


} /* namespace bdd */

#include "Bdd.tpp"