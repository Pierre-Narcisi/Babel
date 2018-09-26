/*
** EPITECH PROJECT, 2018
** babel
** File description:
** Opts.cpp
*/

#include <iostream>
#include "Opts.hpp"

namespace common {

Opts::Opts(int ac, char **av): _ac(ac), _av(av) {}

void	Opts::parse(void) {
	IValue		*val = nullptr;
	static auto	parseShort = [this] (const char curArg) -> typeof(val) {
		const auto matched = _shortRef.find(curArg);

		if (matched == _shortRef.end())
			return nullptr;
		else
			return matched->second.get();
	};

	static auto	parseLong = [this] (const std::string &curArg) -> typeof(val) {
		const auto matched = _longRef.find(curArg);

		if (matched == _longRef.end())
			return nullptr;
		else
			return matched->second.get();
	};

	for (int i = 1; i < _ac; ++i) {
		const std::string	curArg(_av[i]);
		
		val = nullptr;
		if (curArg[0] == '-') {
			if (curArg[1] == '-') {
				val = parseLong(curArg.substr(2));
			} else {
				val = parseShort(curArg[1]);
			}
		}
		if (val
		&& (val->noValue() == false)
		&& (i < _ac - 1))
			val->parse(_av[++i]);
	}
}

}