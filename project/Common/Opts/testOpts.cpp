/*
** EPITECH PROJECT, 2018
** babel
** File description:
** testOpts.cpp
*/

#include <iostream>
#include "Opts.hpp"

int main(int ac, char **av) {
	common::Opts	opts(ac, av);

	opts.setOptions({
		{"port", 'p', common::Opts::makeInt(32)},
		{"test", 0, common::Opts::makeString()},
		{"", 'f', common::Opts::makeFloat(42.42)}
	});

	opts.parse();
	std::cout <<
		"port : " << opts["port"]->as<common::Opts::Int>() << std::endl <<
		"test : " << opts["test"]->as<common::Opts::String>() << std::endl <<
		"f : " << opts["f"]->as<common::Opts::Float>() << std::endl;
		
}