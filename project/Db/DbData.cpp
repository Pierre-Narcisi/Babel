/*
** EPITECH PROJECT, 2018
** babel
** File description:
** DbData.cpp
*/

#include "DbData.h"

namespace db {

Data::Data(Type type)
{
	switch (type) {
		case Type::Number:
			_data = std::make_shared<db::Number>(db::Number{0});
			break;
		case Type::Float:
			_data = std::make_shared<db::Float>(db::Float{0.f});
			break;
		case Type::String:
			_data = std::make_shared<db::String>(db::String{""});
			break;
	}
}



template<>
Data::Data<float>(float f):
_data{std::make_shared<db::Float>(db::Float{f})}
{}

template<>
Data::Data<double>(double d):
_data{std::make_shared<db::Float>(db::Float{d})}
{}

template<>
Data::Data<std::string const &>(std::string const &str):
_data{std::make_shared<db::String>(db::String{str})}
{}

template<>
Data::Data<std::string>(std::string str):
_data{std::make_shared<db::String>(db::String{str})}
{}

template<>
Data::Data<char const *>(char const *str):
_data{std::make_shared<db::String>(db::String{str})}
{}



template<>
float		Data::to<float>() const
{
	if (_data->getType() == Data::Type::Float)
		return static_cast<float>(reinterpret_cast<db::Float *>(_data.get())->data);
	throw std::runtime_error{"to<Float> : error data type"};
}
template<>
double		Data::to<double>() const
{
	if (_data->getType() == Data::Type::Float)
		return reinterpret_cast<db::Float *>(_data.get())->data;
	throw std::runtime_error{"to<Float> : error data type"};
}
template<>
std::string	Data::to<std::string>() const
{
	if (_data->getType() == Data::Type::String)
		return *reinterpret_cast<db::String *>(_data.get());
	throw std::runtime_error{"to<String> : error data type"};
}

} /* namespace Db */