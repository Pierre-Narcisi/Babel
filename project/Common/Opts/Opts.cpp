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
	static auto	parseShort = [this] (const char curArg) -> IValue* {
		const auto matched = _shortRef.find(curArg);

		if (matched == _shortRef.end())
			return nullptr;
		else
			return matched->second.get();
	};

	static auto	parseLong = [this] (const std::string &curArg) -> IValue* {
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
		if (val) {
			val->incCounter();
			if ((val->noValue() == false)
			&& (i < _ac - 1))
				val->parse(_av[++i]);
		}
	}
}

std::ostream	&operator<<(std::ostream &to, Opts const &me) {
	if (me._usageTitle.empty() == false)
		to << me._usageTitle << ":" << std::endl << '\t';
	if (me._usageBody.empty() == false)
		to << me._usageBody << std::endl << std::endl;
	if (me._argsTitle.empty() == false)
		to << me._argsTitle << ":" << std::endl;
	for (auto &val: me._vals) {
		to << '\t' << (*val) << std::endl;
	}
	return to;
}

std::ostream	&operator<<(std::ostream &to, Opts::IValue const &me) {
	int	len = 0;
	if (me._helpName.empty() == false) {
		to << me._helpName;
		len = me._helpName.size();
	}
	for (int i = 0; i < (*me._biggestNamePtr - len) + 3; ++i)
		to << ' ';
	if (me._strHelp.empty() == false) {
		to << '\t' << me._strHelp << (me._def.empty() ? "" :
			(std::string(" (default: ") + me._def + ")"));
	}
	return to;
}

}