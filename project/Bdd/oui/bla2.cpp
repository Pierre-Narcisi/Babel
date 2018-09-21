
#include <iostream>
#include <vector>
#include <string>

class A {};

template<typename T>
class B : public A {
public:
	template<typename V = T>
	void set(V &&t)
	{
		_t = t;
	}
	T &get()
	{
		return _t;
	}
private:
	T _t;
};

int main()
{
	{
		A *b = new B<int>;

		reinterpret_cast<B<int>*>(b)->set(42);
		int i = 3;
		reinterpret_cast<B<int>*>(b)->set(i);
		std::cout << reinterpret_cast<B<int>*>(b)->get() << std::endl;
		std::cout << "-------------" << std::endl;
	}
}