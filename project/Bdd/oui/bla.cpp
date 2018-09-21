
#include <iostream>
#include <vector>
#include <string>

template<typename T, typename U>
U defaultSerialize(T &&t)
{
	return U{t};
}

template<typename T, typename U>
T defaultDeserialize(U const &u)
{
	return T{u};
}

template<typename T, typename U = T, U (*Serialize)(T const &) = defaultSerialize, T (*Deserialize)(U const &) = defaultDeserialize>
class Bdd {
public:
	template<typename TT = T>
	void insert(TT &&t)
	{
		us.push_back(Serialize(t));
	}

	T get(int i)
	{
		return Deserialize(us[i]);
	}
private:
	std::vector<U> us;
};

struct A {
	int i;
};

struct B {
	int i;
	std::string str;
};

A btoa(B const &c)
{
	return A{c.i};
}

B atob(A const &b)
{
	return B{b.i, std::to_string(b.i)};
}

int main()
{
	Bdd<A> a;
	Bdd<B, A, btoa, atob> b;

	a.insert({42});

	std::cout << a.get(0).i << std::endl;

	B c{42, std::to_string(24)};

	b.insert(c);

	auto d = b.get(0);
	std::cout << d.i << " " << d.str << std::endl;
}