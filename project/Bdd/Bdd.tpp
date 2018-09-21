/*
** EPITECH PROJECT, 2018
** babel
** File description:
** Bdd.tpp
*/

#pragma once

#include "Bdd.h"

namespace bdd {

template<typename T>
void Table::setSerializer(serializer_t<T> serializer)
{
	_bdd.setSerializer(serializer, _name);
}

template<typename T>
void Table::setDeserializer(deserializer_t<T> deserializer)
{
	_bdd.setDeserializer(deserializer, _name);
}

template<typename T>
T Table::get(size_t key)
{
	return _bdd.get<T>(key);
}


template<typename T, typename U>
void Bdd::createTable(
	std::string const &tableName,
	std::vector<std::pair<std::string, Data::Type>> const &descriptions,
	serializer_t<T> serializer,
	deserializer_t<U> deserializer)
{
	_tables.emplace(tableName, Table{*this, tableName});
	_tables.at(tableName).setDescription("primary_key", Data::Type::Number);
	if (serializer)
		_tables.at(tableName).setSerializer(serializer);
	if (deserializer)
		_tables.at(tableName).setDeserializer(deserializer);
	for (auto e : descriptions) {
		_tables.at(tableName).setDescription(e.first, e.second);
	}
}


template<typename T>
void Bdd::setSerializer(serializer_t<T> serializer, std::string const &tableName)
{
	_serializers[std::string{typeid(T).name()}] = std::make_pair(tableName, reinterpret_cast<void *>(serializer));
}

template<typename T>
void Bdd::setDeserializer(deserializer_t<T> deserializer, std::string const &tableName)
{
	_deserializers[std::string{typeid(T).name()}] = std::make_pair(tableName, reinterpret_cast<void *>(deserializer));
}

template<typename T>
Bdd::Key Bdd::insert(T const &t)
{
	std::pair<std::string, void *> serializerInfo = _serializers[typeid(T).name()];
	Key key = _tables.at(serializerInfo.first).newElement();

	reinterpret_cast<serializer_t<T>>(serializerInfo.second)(t, _tables.at(serializerInfo.first)[key]);

	return key;
}


}