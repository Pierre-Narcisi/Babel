/*
** EPITECH PROJECT, 2018
** babel
** File description:
** Protocol.h
*/

#pragma once

#include <string>

namespace babel {

namespace protocol {

/* Common */
struct Respond {
	bool respond;
};

/* Client -> Server */
struct Connect {
	char		username[128];
	char		password[128];
};

struct getMessages {
	char		username[128];
	std::size_t	start;
	std::size_t	number;
};

struct Update {
	enum class Type {Logo, User, Friend};
	Type		type;
};
struct UpdateLogo : public Update {
	std::size_t	size;
	char		buffer[];
};
struct UpdateUser : public Update {
	char		username[128];
	char		password[128];
};
struct UpdateFriend : public Update {
	enum class What {Update, Erase};
	What		what;
	char		username[128];
	char		name[128];
};

struct Send {
	char		username[128];
	std::size_t	size;
	char		bla[];
};

/* Server -> Client */
struct updateClient {
	char		username[128];
	std::size_t	size;
	char		buffer[];
};

struct updateFriend {
	bool		state;
	char		username[128];
	char		name[128];
	std::size_t	size;
	char		icon[];
};

struct updateMessage {
	struct Message {
		std::size_t	size;
		char		buffer[];
	};
	char		username[128];
	std::size_t	nbMessage;
	Message		messages[];
};


} /* protocol */

} /* babel */
