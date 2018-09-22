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
Data::Data<float>(float f);
template<>
Data::Data<double>(double d);
template<>
Data::Data<std::string const &>(std::string const &str);
template<>
Data::Data<std::string>(std::string str);
template<>
Data::Data<char const *>(char const *str);


template<typename T>
T		Data::to() const
{
	if (_data->getType() == Data::Type::Number)
		return static_cast<T>(reinterpret_cast<db::Number *>(_data.get())->data);
	throw std::runtime_error{"to<Number> : error data type"};
}
template<>
float		Data::to<float>() const;
template<>
double		Data::to<double>() const;
template<>
std::string	Data::to<std::string>() const;


} /* namespace db */