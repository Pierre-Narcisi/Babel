/*
** EPITECH PROJECT, 2018
** babel
** File description:
** BddData.h
*/

#pragma once

#include <string>
#include <ctime>
#include <memory>

namespace bdd {

class AbstractData;

class Data {
public:
	enum class Type { Number = 0, Float = 1, String = 2/*, Date */};
	using Number = long;
	using Float = double;
	using String = std::string;
	// using Date = std::time_t;

	Data(Type);

	template<typename T>
	Data(T t);

	template<typename T>
	T	&to();

	template<typename T>
	T const	&to() const;

private:
	std::shared_ptr<AbstractData> _data;
};

class AbstractData  {
public:
	virtual Data::Type getType() const = 0;
};

struct Number : public AbstractData {
	template<typename T>
	Number(T &&t): data{static_cast<long long>(t)} {}

	operator bdd::Data::Number() { return data; }

	Data::Type getType() const override { return Data::Type::Number; }

	bdd::Data::Number data;
};

struct Float : public AbstractData {
	Float(bdd::Data::Float d): data{d} {}

	operator bdd::Data::Float() { return data; }

	Data::Type getType() const override { return Data::Type::Float; }

	bdd::Data::Float data;
};

struct String : public AbstractData {
	String(bdd::Data::String const &str): data{str} {}

	operator bdd::Data::String() { return data; }

	Data::Type getType() const override { return Data::Type::String; }

	bdd::Data::String	data;
};

// struct Date : public AbstractData {
// 	Date(bdd::Data::Date timestamp): data{timestamp} {}

// 	operator bdd::Data::Date() { return data; }

// 	Data::Type getType() const override { return Data::Type::Date; }

// 	bdd::Data::Date data;
// };

} /* namespace bdd */

#include "BddData.tpp"
