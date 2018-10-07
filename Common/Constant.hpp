/*
** EPITECH PROJECT, 2018
** babel
** File description:
** Const.hpp
*/

#pragma once

#include <string>

namespace constant {
    /* Server Program default args */
	constexpr std::uint16_t		defPort = 4242;
	constexpr char const		*defDbFileName = ".db";
	constexpr char const		*defUserFileIcon = "defaultIcon.jpeg";
#ifdef __linux__
	constexpr char const		*ressourcesFolder = ".ressources/";
#else
	constexpr char const		*ressourcesFolder = ".\\.ressources\\";
#endif
	constexpr std::uint16_t		defThreadNbr = 4;

    /* Client Program default args */
#ifdef QT_DEBUG
    constexpr char const        *defHost = "localhost";
#else
    constexpr char const        *defHost = "holidev.net";
#endif
}
