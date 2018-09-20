#include "Epoll.hpp"
#include <iostream>

int main()
{
	CC::EPoll Ah;

	Ah.add(0, [] (int fd) -> int {
		char buffer[1024];

		int a = read(fd, buffer, 1023);
		buffer[a] = '\0';
		std::cout << buffer << std::endl;
		return (0);
	});
	Ah.wait();
	return (0);
}