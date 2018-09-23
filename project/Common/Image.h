/*
** EPITECH PROJECT, 2018
** babel
** File description:
** Image.h
*/

#pragma once

#include <string>
#include <ctime>

namespace babel {

// image pour le client == lien de l'image sur son pc
// serveur -> client : envoie le liens de l'image en relatif (ex: .store/icon_1.png) + un truc pour verifier que c'est la bonne (hash taille + date ?)
// si le client n'a pas la bonne version il peut la télécharger sur le serveur
struct Image {
	std::string link;
	std::size_t size;
	std::time_t timestampCreation;
};

}