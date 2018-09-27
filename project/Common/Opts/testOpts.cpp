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

	opts.setUsage("Usage", std::string(av[0]) + " [-p port]");
	opts.setArgsTitle("Available Arguments");
	opts.setOptions({
		{"help", 'h', common::Opts::noArg(), "Show this help"},
		{"port", 'p', common::Opts::makeInt(32), "Listening port"},
		{"test", 0, common::Opts::makeString(), "Test string"},
		{"", 'f', common::Opts::makeFloat(42.42), "test Float"}
	});

	opts.parse();
	if (opts["help"]->count())
		std::cout << opts << std::endl;

	std::cout <<
		"port : " << opts["port"]->as<common::Opts::Int>() << std::endl <<
		"test : " << opts["test"]->as<common::Opts::String>() << std::endl <<
		"f : " << opts['f']->as<common::Opts::Float>() << std::endl;
		
}