
#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <unordered_map>
#include <memory>

class Bdd;

template<typename T>
class BddArray : public std::vector<T> {
public:
	BddArray<T>(Bdd &bdd): _bdd{bdd} {}

	template<typename U>
	BddArray<U> deserialize(U (*deserializer)(T const &)) const
	{
		BddArray<U> arr{_bdd};

		for (auto const &e : *this) {
			arr.push_back(deserialize(e));
		}
		return arr;
	}
private:
	Bdd	&_bdd;
};

class Bdd {
private:
	class IChamp {};

	template<typename T>
	class Champ : public IChamp {
	public:
		Champ(Bdd &bdd): _bdd{bdd}, _datas{bdd} {}

		template<typename TT = T>
		void put(TT &&t)
		{
			_datas.push_back(t);
		}

		T const &operator[](size_t i) const
		{
			return _datas[i];
		}

		BddArray<T> const &getAll() const
		{
			return _datas;
		}

	private:
		Bdd	&_bdd;
		BddArray<T> _datas;
	};

public:
	template<typename T, typename ...Args>
	using serializer_t = void (*)(T &&, Bdd &, Args...);

	template<typename T, typename ...Args>
	using deserializer_t = T (*)(Bdd &, Args...);

public:
	template<typename T>
	Champ<T> &get()
	{
		auto it = _champs.find(typeid(T).name());
		if (it == _champs.end()) {
			auto champ = std::make_unique<Champ<T>>(*this);
			auto ptr = champ.get();

			_champs[typeid(T).name()] = std::move(champ);
			return *ptr;
		} else {
			return *reinterpret_cast<Champ<T> *>(it->second.get());
		}
	}

	template<typename T, typename ...Args>
	void setSerializer(serializer_t<T, Args...> serializer)
	{
		_serializers[typeid(T).name()] = reinterpret_cast<void *>(serializer);
	}

	template<typename T, typename ...Args>
	void setDeserializer(deserializer_t<T, Args...> deserializer)
	{
		_deserializers[typeid(T).name()] = reinterpret_cast<void *>(deserializer);
	}

	template<typename T, typename ...Args>
	void serialize(T &&t, Args &&...args)
	{
		reinterpret_cast<serializer_t<T, Args...>>(_serializers[typeid(T).name()])(std::forward<T>(t), *this, args...);
	}
	template<typename T, typename ...Args>
	T deserialize(Args &&...args)
	{
		return reinterpret_cast<deserializer_t<T, Args...>>(_deserializers[typeid(T).name()])(*this, args...);
	}


private:
	std::unordered_map<std::string, void * /*aka serializer_t*/>	_serializers;
	std::unordered_map<std::string, void * /*aka deserializer_t*/>	_deserializers;
	std::unordered_map<std::string, std::unique_ptr<IChamp>>	_champs;
};

template<typename T = int>
void serializeInt(T &&t, Bdd &bdd, int i)
{
	bdd.get<std::string>().put(std::to_string(t + i));
}

int deserializeInt(Bdd &bdd, int &i)
{
	return std::stoi(bdd.get<std::string>()[0]) - i;
}

struct A {
	int	i;
	float	f;
};

struct B {
	std::string str;
};

template<typename T = A>
void serializeA(T &&t, Bdd &bdd)
{
	std::stringstream sstr;
	sstr << t.i << ":" << t.f;
	bdd.get<B>().put({sstr.str()});
}
A deserializeA(Bdd &bdd)
{
	std::stringstream sstr{bdd.get<B>()[0].str};
	char c;
	A a;
	sstr >> a.f >> c >> a.i;
	return a;
}

int main()
{
	Bdd b;

	b.get<B>();
	// b.setSerializer<int, int>(serializeInt);
	// b.setDeserializer<int, int&>(deserializeInt);
	// b.serialize(42, 12);
	// int i = 42;
	// std::cout << b.deserialize<int>(i) << std::endl;

	// std::cout << "------------" << std::endl;

	// b.setSerializer<A>(serializeA);
	// b.setDeserializer<A>(deserializeA);

	// b.serialize(A{32, 55.31});
	// A a = b.deserialize<A>();
	// std::cout << a.i << " " << a.f << std::endl;
}