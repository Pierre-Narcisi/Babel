/*
** EPITECH PROJECT, 2018
** babel
** File description:
** DbData.tpp
*/

#include "DbData.h"

#pragma once

namespace db {

template<typename T>
Data::Data(T t):
_data{std::make_shared<db::Number>(db::Number{t})}
{}

template<>
Data::Data(float f);
template<>
Data::Data(double d);
template<>
Data::Data(std::string const &str);
template<>
Data::Data(std::string str);
template<>
Data::Data(char const *str);


template<typename T>
T		Data::as() const
{
	if (_data->getType() == Data::Type::Number)
		return static_cast<T>(reinterpret_cast<db::Number *>(_data.get())->data);
	throw std::runtime_error{"to<Number> : error data type"};
}
template<>
float		Data::as() const;
template<>
double		Data::as() const;
template<>
std::string	Data::as() const;


} /* namespace db */