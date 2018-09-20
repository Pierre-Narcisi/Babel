/*
** EPITECH PROJECT, 2018
** BDD
** File description:
** Bdd.cpp
*/

#include <iostream>

#include "Bdd.h"

struct A {
	friend std::ostream &operator<<(std::ostream &os, A const &a)
	{
		return os << a.i;
	}
	int i;
};

int main()
{
	bdd::Bdd<A> bddA;

	// auto idx = bddA.insert(A{42});

	auto idx1 = bddA.insert(A{10});
	auto idx2 = bddA.insert(A{11});
	auto idx3 = bddA.insert(A{12});
	auto idx4 = bddA.insert(A{13});

	std::cout << "Bdd:\n" << bddA << std::endl;

	bddA.erase(idx2);
	std::cout << "Bdd:\n" << bddA << std::endl;
	bddA.erase(idx1);
	std::cout << "Bdd:\n" << bddA << std::endl;
	bddA.erase(idx4);
	std::cout << "Bdd:\n" << bddA << std::endl;

	// bddA.erase(-1);

	// std::cout << idx << "  " << bddA[idx].i << std::endl;
	// bddA[idx].i -= 10;
	// bddA.insert(A{24});
	// bddA.insert(A{25});
	// bddA.insert(A{26});
	// std::cout << "Bdd:\n" << bddA << std::endl;
	// std::cout << idx << "  " << bddA[idx].i << std::endl;
	// bddA.erase(idx);
	// std::cout << idx << "  " << bddA[idx].i << std::endl;
	// bddA.erase(2);
	// std::cout << "Bdd:\n" << bddA << std::endl;
	// std::cout << idx << "  " << bddA[idx].i << std::endl;
}