/*
** EPITECH PROJECT, 2018
** babel
** File description:
** BddData.cpp
*/

#include "BddData.h"

namespace bdd {

bdd::Data::Data(Type type)
{
	switch (type) {
		case Type::Number:
			_data = std::make_shared<bdd::Number>(bdd::Number{0});
			break;
		case Type::Float:
			_data = std::make_shared<bdd::Float>(bdd::Float{0.f});
			break;
		case Type::String:
			_data = std::make_shared<bdd::String>(bdd::String{""});
			break;
		case Type::Key:
			_data = std::make_shared<bdd::Key>(bdd::Key{0, ""});
			break;
		// case Type::Date:
			// _data = std::make_shared<bdd::Date>(bdd::Date{time()});
			// break;
	}
}



template<>
bdd::Data::Data<float>(float f):
_data{std::make_shared<bdd::Float>(bdd::Float{f})}
{}

template<>
bdd::Data::Data<double>(double d):
_data{std::make_shared<bdd::Float>(bdd::Float{d})}
{}

template<>
bdd::Data::Data<std::string const &>(std::string const &str):
_data{std::make_shared<bdd::String>(bdd::String{str})}
{}

template<>
bdd::Data::Data<std::string>(std::string str):
_data{std::make_shared<bdd::String>(bdd::String{str})}
{}

template<>
bdd::Data::Data<char const *>(char const *str):
_data{std::make_shared<bdd::String>(bdd::String{str})}
{}

template<>
bdd::Data::Data<bdd::Key>(bdd::Key key):
_data{std::make_shared<bdd::Key>(key)}
{}

// template<>
// bdd::Data::Data<std::time_t>(std::time_t timestamp):
// _data{std::make_shared<bdd::Date>(bdd::Date{timestamp})}
// {}



template<>
bdd::Data::Number	&bdd::Data::to<bdd::Data::Number>()
{
	if (_data->getType() == Data::Type::Number)
		return reinterpret_cast<bdd::Number *>(_data.get())->data;
	throw std::runtime_error{"to<Number> : error data type"};
}

template<>
bdd::Data::Float	&bdd::Data::to<bdd::Data::Float>()
{
	if (_data->getType() == Data::Type::Float)
		return reinterpret_cast<bdd::Float *>(_data.get())->data;
	throw std::runtime_error{"to<Float> : error data type"};
}
template<>
bdd::Data::String	&bdd::Data::to<bdd::Data::String>()
{
	if (_data->getType() == Data::Type::String)
		return *reinterpret_cast<bdd::String *>(_data.get());
	throw std::runtime_error{"to<String> : error data type"};
}

template<>
bdd::Data::Key		&bdd::Data::to<bdd::Data::Key>()
{
	if (_data->getType() == Data::Type::Key)
		return *reinterpret_cast<bdd::Key *>(_data.get());
	throw std::runtime_error{"to<Key> : error data type"};
}

// template<>
// bdd::Data::Date	&bdd::Data::to<bdd::Data::Date>()
// {
// 	if (_data->getType() == Data::Type::Date)
// 		return reinterpret_cast<bdd::Date *>(_data.get())->data;
// 	throw std::runtime_error{"error data type"};
// }



template<>
bdd::Data::Number const		&bdd::Data::to<bdd::Data::Number>() const
{
	if (_data->getType() == Data::Type::Number)
		return reinterpret_cast<bdd::Number *>(_data.get())->data;
	throw std::runtime_error{"to<Number> : error data type"};
}

template<>
bdd::Data::Float const		&bdd::Data::to<bdd::Data::Float>() const
{
	if (_data->getType() == Data::Type::Float)
		return reinterpret_cast<bdd::Float *>(_data.get())->data;
	throw std::runtime_error{"to<Float> : error data type"};
}

template<>
bdd::Data::String const		&bdd::Data::to<bdd::Data::String>() const
{
	if (_data->getType() == Data::Type::String)
		return *reinterpret_cast<bdd::String *>(_data.get());
	throw std::runtime_error{"to<String> : error data type"};
}

template<>
bdd::Data::Key const		&bdd::Data::to<bdd::Data::Key>() const
{
	if (_data->getType() == Data::Type::Key)
		return *reinterpret_cast<bdd::Key *>(_data.get());
	throw std::runtime_error{"to<Key> : error data type"};
}


// template<>
// bdd::Data::Date const	&bdd::Data::to<bdd::Data::Date>() const
// {
// 	if (_data->getType() == Data::Type::Date)
// 		return reinterpret_cast<bdd::Date *>(_data.get())->data;
// 	throw std::runtime_error{"error data type"};
// }

} /* namespace bdd */