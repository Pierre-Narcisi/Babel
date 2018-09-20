
#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <unordered_map>
#include <memory>

class Bdd {
private:
	class IChamp {};

	template<typename T>
	class Champ : public IChamp {
	public:
		Champ(Bdd &bdd): _bdd{bdd} {}

		void print(T t)
		{
			std::cout << t << std::endl;
		}

		template<typename TT = T>
		void put(TT &&t)
		{
			_t = t;
		}

		T &get()
		{
			return _t;
		}

	private:
		Bdd	&_bdd;
		T	_t;
	};

public:
	template<typename T>
	using serializer_t = void (*)(T &&, Bdd &);

	template<typename T>
	using deserializer_t = T (*)(Bdd &);

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

	template<typename T>
	void setSerializer(serializer_t<T> serializer)
	{
		_serializers[typeid(T).name()] = reinterpret_cast<void *>(serializer);
	}

	template<typename T>
	void setDeserializer(deserializer_t<T> deserializer)
	{
		_deserializers[typeid(T).name()] = reinterpret_cast<void *>(deserializer);
	}

	template<typename T>
	void serialize(T &&t)
	{
		reinterpret_cast<serializer_t<T>>(_serializers[typeid(T).name()])(std::forward<T>(t), *this);
	}
	template<typename T>
	T deserialize()
	{
		return reinterpret_cast<deserializer_t<T>>(_deserializers[typeid(T).name()])(*this);
	}


private:
	std::unordered_map<std::string, void * /*aka serializer_t*/>	_serializers;
	std::unordered_map<std::string, void * /*aka deserializer_t*/>	_deserializers;
	std::unordered_map<std::string, std::unique_ptr<IChamp>>	_champs;
};

template<typename T = int>
void serializeInt(T &&t, Bdd &bdd)
{
	bdd.get<std::string>().put(std::to_string(t));
}

int deserializeInt(Bdd &bdd)
{
	return std::stoi(bdd.get<std::string>().get());
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
	std::stringstream sstr{bdd.get<B>().get().str};
	char c;
	A a;
	sstr >> a.f >> c >> a.i;
	return a;
}

int main()
{
	Bdd b;

	b.get<int>().print(42);
	b.get<int>().print(33);
	b.get<std::string>().print("coucou");
	std::cout << "------------" << std::endl;

	b.setSerializer<int>(serializeInt);
	b.setDeserializer<int>(deserializeInt);
	b.serialize(42);
	std::cout << b.deserialize<int>() << std::endl;

	std::cout << "------------" << std::endl;

	b.setSerializer<A>(serializeA);
	b.setDeserializer<A>(deserializeA);

	b.serialize(A{32, 55.31});
	A a = b.deserialize<A>();
	std::cout << a.i << " " << a.f << std::endl;
}