/*
** EPITECH PROJECT, 2018
** babel
** File description:
** Db.h
*/

#pragma once

#include <functional>
#include <iostream>
#include <vector>
#include <list>
#include <string>
#include <unordered_map>

#include "DbData.h"

namespace db {

class Db;
class Table;
class Element;

using Key = std::size_t;

template<typename T>
using serializer_t = void (*)(T const &, Element &, db::Db &);
template<typename T>
using deserializer_t = T (*)(Element &, db::Db &);

using remover_t = void (*)(Element &, db::Db &);

class Array : public std::list<Element> {
public:
	Array where(std::function<bool (Element const &)> const &) const;
};

class Table {
/* à plusieurs Element. ex: db["sushi"][0] ou db["vehicule"][1] */
public:
	Table(Db &db, std::string const &name): _db{db}, _name{name} {}

	void setDescription(std::string const &dataName, Data::Type type);

	template<typename T>
	void setSerializer(serializer_t<T> serializer);
	template<typename T>
	void setDeserializer(deserializer_t<T> deserializer);

	void setRemover(remover_t remover);

	void remove(Key key);
	void remove_if(std::function<bool (Element const &)> const &func);

	template<typename T>
	T get(Key key);

	Array &getAll();

	std::unordered_map<std::string, Data::Type> const &getDescription() const;

	Key newElement();

	Element &operator[](Key key);

	friend std::ostream &operator<<(std::ostream &os, Table const &champ);

private:
	Db						&_db;
	std::string					_name;
	remover_t					_remover = nullptr;
	std::unordered_map<std::string, Data::Type>	_description;
	Array						_elements;
	Key						_lastElementKey = 0;
}; /* class Table */


class Db {
/* à plusieurs Table. ex: db["sushi"] ou db["vehicule"] */
public:

	template<typename T = void *, typename U = void *>
	void createTable(
		std::string const &tableName,
		std::vector<std::pair<std::string, Data::Type>> const &descriptions,
		serializer_t<T> serializer = nullptr,
		deserializer_t<U> deserializer = nullptr,
		remover_t remover = nullptr);


	template<typename T>
	void setSerializer(serializer_t<T> serializer, std::string const &tableName);
	template<typename T>
	void setDeserializer(deserializer_t<T> deserializer, std::string const &tableName);
	
	template<typename T>
	T get(Key key);

	template<typename T>
	Key insert(T const &);

	Table &operator[](std::string const &tableName);

	friend std::ostream &operator<<(std::ostream &os, Db const &db);

private:
	std::unordered_map<std::string, Table>		_tables;
	std::unordered_map<std::string, std::pair<std::string, void * /*aka serializer_t*/>>	_serializers;
	std::unordered_map<std::string, std::pair<std::string, void * /*aka deserializer_t*/>>	_deserializers;
}; /* class Db */


class Element {
/* à plusieurs data. ex: db["sushi"][0]["riz"] ou db["vehicule"][0]["nb_roue"] */
public:
	Element(Table &table);

	Element(Element const &) = default;
	Element &operator=(Element const &) = default;
	Element(Element &&) = default;
	Element &operator=(Element &&) = default;

	Data &operator[](std::string const &dataName);
	Data const &operator[](std::string const &dataName) const;

	friend std::ostream &operator<<(std::ostream &os, Element const &element);

private:
	Table						&_table;
	std::unordered_map<std::string, Data>		_datas;
}; /* class Element */


} /* namespace db */

#include "Db.tpp"