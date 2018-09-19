/*
** EPITECH PROJECT, 2018
** ProjAudio
** File description:
** Server.h
*/

#pragma once

#include "Bdd.h"

namespace babel {

class Server {
public:

private:
	bdd::Bdd<ClientInfo> clientBdd;
};

}