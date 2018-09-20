
#include <memory>
#include <ctime>
#include <iostream>

#include "BddData.h"

int main()
{
	bdd::Data data = 42;
	bdd::Data data2 = 42.42;
	bdd::Data data3 = "oui";
	std::string str = "bla";
	bdd::Data data4 = str;
	bdd::Data data5 = time(nullptr);

	data = 12;
	data4 = "pourquoi";
	std::cout << data.to<bdd::Data::Number>() << std::endl;
	std::cout << data.to<long>() << std::endl;
	std::cout << data2.to<bdd::Data::Float>() << std::endl;
	std::cout << data3.to<bdd::Data::String>() << std::endl;
	std::cout << data4.to<bdd::Data::String>() << std::endl;
	// std::cout << asctime(localtime(&data5.to<bdd::Data::Date>()));
	std::cout << asctime(localtime(&data5.to<long>()));
}