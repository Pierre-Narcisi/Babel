/*
** EPITECH PROJECT, 2018
** babel
** File description:
** Db.tpp
*/

#pragma once

#include "Db.h"

namespace db {

template<typename T>
void Table::setSerializer(serializer_t<T> serializer)
{
	_db.setSerializer(serializer, _name);
}

template<typename T>
void Table::setDeserializer(deserializer_t<T> deserializer)
{
	_db.setDeserializer(deserializer, _name);
}

template<typename T>
T Table::get(Key key)
{
	return _db.get<T>(key);
}


template<typename T, typename U>
void Db::createTable(
	std::string const &tableName,
	std::vector<std::pair<std::string, Data::Type>> const &descriptions,
	serializer_t<T> serializer,
	deserializer_t<U> deserializer,
	remover_t remover)
{
	_tables.emplace(tableName, Table{*this, tableName});
	_tables.at(tableName).setDescription("primary_key", Data::Type::Number);
	if (serializer)
		_tables.at(tableName).setSerializer(serializer);
	if (deserializer)
		_tables.at(tableName).setDeserializer(deserializer);
	if (remover)
		_tables.at(tableName).setRemover(remover);
	for (auto e : descriptions) {
		_tables.at(tableName).setDescription(e.first, e.second);
	}
}


template<typename T>
void Db::setSerializer(serializer_t<T> serializer, std::string const &tableName)
{
	_serializers[std::string{typeid(T).name()}] = std::make_pair(tableName, reinterpret_cast<void *>(serializer));
}

template<typename T>
void Db::setDeserializer(deserializer_t<T> deserializer, std::string const &tableName)
{
	_deserializers[std::string{typeid(T).name()}] = std::make_pair(tableName, reinterpret_cast<void *>(deserializer));
}

template<typename T>
Key Db::insert(T const &t)
{
	std::pair<std::string, void *> serializerInfo = _serializers[typeid(T).name()];
	Key key = _tables.at(serializerInfo.first).newElement();

	reinterpret_cast<serializer_t<T>>(serializerInfo.second)(t, _tables.at(serializerInfo.first)[key], *this);

	return key;
}

template<typename T>
T Db::get(Key key)
{
	std::pair<std::string, void *> deserializerInfo = _deserializers[typeid(T).name()];
	return reinterpret_cast<deserializer_t<T>>(deserializerInfo.second)(_tables.at(deserializerInfo.first)[key], *this);
}


}