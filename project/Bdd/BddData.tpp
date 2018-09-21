/*
** EPITECH PROJECT, 2018
** babel
** File description:
** BddData.tpp
*/

#include "BddData.h"

#pragma once

namespace bdd {

template<typename T>
bdd::Data::Data(T t):
_data{std::make_shared<bdd::Number>(bdd::Number{t})}
{}


template<>
bdd::Data::Data<float>(float f);

template<>
bdd::Data::Data<double>(double d);

template<>
bdd::Data::Data<std::string const &>(std::string const &str);

template<>
bdd::Data::Data<std::string>(std::string str);

template<>
bdd::Data::Data<char const *>(char const *str);

template<>
bdd::Data::Data<bdd::Key>(bdd::Key key);

// template<>
// Data<Data::Date>(Data::Date timestamp);



template<>
bdd::Data::Number	&bdd::Data::to<bdd::Data::Number>();

template<>
bdd::Data::Float	&bdd::Data::to<bdd::Data::Float>();
template<>
bdd::Data::String	&bdd::Data::to<bdd::Data::String>();

template<>
bdd::Data::Key		&bdd::Data::to<bdd::Data::Key>();

// template<>
// bdd::Data::Date		&bdd::Data::to<Data::Date>();



template<>
bdd::Data::Number const		&bdd::Data::to<bdd::Data::Number>() const;

template<>
bdd::Data::Float const		&bdd::Data::to<bdd::Data::Float>() const;

template<>
bdd::Data::String const		&bdd::Data::to<bdd::Data::String>() const;

template<>
bdd::Data::Key const		&bdd::Data::to<bdd::Data::Key>() const;
// template<>
// bdd::Data::Date const	&bdd::Data::to<bdd::Data::Date>() const;

} /* namespace bdd */