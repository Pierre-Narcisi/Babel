/*
** EPITECH PROJECT, 2018
** babel
** File description:
** Opts.hpp
*/

#pragma once

#include <map>
#include <string>
#include <memory>

namespace common {

class Opts {
public:
	Opts(int ac, char **av);

	class IValue;
	class Int;
	class String;
	class Float;
	class NoValue;

	static inline std::shared_ptr<IValue>	makeInt(long def = 0);
	static inline std::shared_ptr<IValue>	makeFloat(double def = 0.0);
	static inline std::shared_ptr<IValue>	makeString(std::string &&def = "");
	static inline std::shared_ptr<IValue>	noArg();

	inline void	setOptions(std::initializer_list<std::tuple<std::string, char, std::shared_ptr<IValue>>> &&in) {
		for (auto &i: in) {
			auto &lRef = std::get<0>(i);
			auto shRef = std::get<1>(i);
			auto &valType = std::get<2>(i);

			if (lRef.size() != 0)
				_longRef[lRef] = valType;
			if (shRef != 0)
				_shortRef[shRef] = valType;
		}
	}

	inline std::shared_ptr<IValue> &operator[](const std::string &name) {
		auto it = _longRef.find(name);

		if (it != _longRef.end())
			return (*it).second;
		auto itShort = _shortRef.find(name.at(0));
		if (itShort != _shortRef.end())
			return (*itShort).second;
		else
			throw std::runtime_error((std::string("Cannot find ") + name).c_str());
	}

	void	parse(void);
private:
	int	_ac;
	char	**_av;

	std::map<const std::string, std::shared_ptr<IValue>>
		_longRef;
	std::map<const char, std::shared_ptr<IValue>>
		_shortRef;
};

class Opts::IValue {
public:
	explicit IValue(bool noVal = true): _noValue(noVal) {}

	inline bool	noValue() const { return _noValue; }
	
	template<typename T>
	inline typename T::type	as(void) {
		return (reinterpret_cast<T*>(this))->get();
	}

	virtual	void	parse(std::string const &in) = 0;
protected:
private:
	bool	_noValue;
};

class Opts::NoValue : public Opts::IValue {
public:
	NoValue(): IValue(true) {}
	virtual void	parse(std::string const &) final {}
};

class Opts::Int : public Opts::IValue {
public:
	using	type = long;
	Int(type defVal): IValue(false), _val(defVal) {}

	inline void	set(long in) { _val = in; }
	inline type	get(void) { return _val; }
	virtual void	parse(std::string const &in) final { _val = std::stol(in); }
private:
	long	_val;
};

class Opts::String : public Opts::IValue {
public:
	using	type = std::string&;
	String(type defVal): IValue(false), _val(defVal) {}

	inline void		set(std::string &&in) { _val = in; }
	inline type		get(void) { return _val; }
	virtual void		parse(std::string const &in) final { _val = in; }
private:
	std::string	_val;
};

class Opts::Float : public Opts::IValue {
public:
	using type = double;
	Float(type defVal): IValue(false), _val(defVal) {}

	inline void	set(double in) { _val = in; }
	inline type	get(void) { return _val; }
	virtual void	parse(std::string const &in) final { _val = std::stod(in); }
private:
	double	_val;
};

inline std::shared_ptr<Opts::IValue>	Opts::makeInt(long def) {
	return std::shared_ptr<IValue>(reinterpret_cast<IValue*>(new Int(def)));
}

inline std::shared_ptr<Opts::IValue>	Opts::makeFloat(double def) {
	return std::shared_ptr<IValue>(reinterpret_cast<IValue*>(new Float(def)));
}

inline std::shared_ptr<Opts::IValue>	Opts::makeString(std::string &&def) {
	return std::shared_ptr<IValue>(reinterpret_cast<IValue*>(new String(def)));
}

inline std::shared_ptr<Opts::IValue>	Opts::noArg() {
	return std::shared_ptr<IValue>(reinterpret_cast<IValue*>(new NoValue()));
}

}