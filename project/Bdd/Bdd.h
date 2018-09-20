
#pragma once

#include <iostream>
#include <vector>
#include <string>

namespace bdd {

enum class ValueType { Number, String, Date };

class BddManager;

template<typename T, typename U>
U defaultSerialize(T &&t, BddManager &)
{
	return U{t};
}

template<typename T, typename U>
T defaultDeserialize(U const &u, BddManager &)
{
	return T{u};
}

template<
	typename T,
	typename U = T,
	U (*Serialize)(T const &, BddManager &) = defaultSerialize,
	T (*Deserialize)(U const &, BddManager &) = defaultDeserialize>
class Bdd {
public:
	using index = long;
	template<typename TT = T>
	index	insert(TT &&);
	void	erase(index);

	T &operator[](index);

	friend std::ostream &operator<<(std::ostream &os, Bdd<T> const &bdd)
	{
		bool first = true;
		os << "{";
		for (auto const &e : bdd._values) {
			if (!first)
				os << ", ";
			else
				first = false;
			os << "{" << e.first << ", {" << e.second << "}}";
		}
		return os << "}";
	}

private:
	std::vector<std::pair<index, T>> _values;
};

class BddManager {
public:
private:
	template<typename T, typename U = T, U (*Serialize)(T const &, BddManager &) = defaultSerialize, T (*Deserialize)(U const &, BddManager &) = defaultDeserialize>
	Bdd<T, U, Serialize, Deserialize> bdd;
};

}

#include "Bdd.tpp"