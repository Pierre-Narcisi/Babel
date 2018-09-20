
#pragma once

#include <algorithm>

#include "Bdd.h"

namespace bdd {

template<typename T, typename U, U (*Serialize)(T const &), T (*Deserialize)(U const &)>
template<typename TT>
typename Bdd<T, U, Serialize, Deserialize>::index	Bdd<T, U, Serialize, Deserialize>::insert(TT &&t)
{
	_values.push_back(std::make_pair((_values.size() ? _values.back().first + 1: 0), t));
	return (_values.back().first);
}

template<typename T, typename U, U (*Serialize)(T const &), T (*Deserialize)(U const &)>
void	Bdd<T, U, Serialize, Deserialize>::erase(index idx)
{
	if (idx < 0 || idx > _values.back().first)
		throw "out of range";
	if (_values.back().first + 1 == _values.size()) {
		_values.erase(_values.begin() + static_cast<long>(idx));
	} else {
		_values.erase(std::find_if(_values.begin(), _values.end(), [idx](auto const &e){return e.first == idx;}));
	}
}

template<typename T, typename U, U (*Serialize)(T const &), T (*Deserialize)(U const &)>
T	&Bdd<T, U, Serialize, Deserialize>::operator[](index idx)
{
	if (_values.size() == 0)
		throw "out of range";
	if (idx < 0 || idx > _values.back().first)
		throw "out of range";
	if (_values.back().first == _values.size()) {
		return _values[idx].second;
	}
	return std::find_if(_values.begin(), _values.end(), [idx](auto const &e){return e.first == idx;})->second;
}

}