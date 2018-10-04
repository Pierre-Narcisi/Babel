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
	constexpr char const		*defUserFileIcon = "defaultFileIcon.png";
	constexpr std::uint16_t		defThreadNbr = 4;

    /* Client Program default args */
	constexpr char const        *defHost = "holidev.net";
}
