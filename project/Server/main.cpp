/*
** EPITECH PROJECT, 2018
** babel
** File description:
** main.cpp
*/

#include "CoreServer/CoreServer.hpp"

int main(int ac, char **av) {
	srv::CoreServer	srv(ac, av);

	srv.start();
}