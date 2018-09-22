/*
** EPITECH PROJECT, 2018
** babel
** File description:
** DbData.h
*/

#pragma once

#include <string>
#include <ctime>
#include <memory>

namespace db {

class AbstractData;

class Data {
public:
	enum class Type { Number, Float, String, Key/*, Date */};
	using Number = long;
	using Float = double;
	using String = std::string;
	// using Date = std::time_t;

	Data(Type);

	template<typename T>
	Data(T t);

	template<typename T>
	T	to() const;

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

	operator Data::Number() { return data; }

	Data::Type getType() const override { return Data::Type::Number; }

	Data::Number data;
};

struct Float : public AbstractData {
	Float(Data::Float d): data{d} {}

	operator Data::Float() { return data; }

	Data::Type getType() const override { return Data::Type::Float; }

	Data::Float data;
};

struct String : public AbstractData, public Data::String {
	String(Data::String const &str): Data::String{str} {}

	Data::Type getType() const override { return Data::Type::String; }
};

// struct Date : public AbstractData {
// 	Date(Data::Date timestamp): data{timestamp} {}

// 	operator Data::Date() { return data; }

// 	Data::Type getType() const override { return Data::Type::Date; }

// 	Data::Date data;
// };

} /* namespace Db */

#include "DbData.tpp"
