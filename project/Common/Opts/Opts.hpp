/*
** EPITECH PROJECT, 2018
** babel
** File description:
** Opts.hpp
*/

#pragma once

#include <map>
#include <list>
#include <string>
#include <memory>
#include <ostream>

namespace common {

class Opts {
public:
	Opts(int ac, char **av);

	class IValue;
	class Int;
	class String;
	class Float;
	class NoValue;
	class OptionsCont;

	static inline std::shared_ptr<IValue>	makeInt(long def);
	static inline std::shared_ptr<IValue>	makeInt(void);
	static inline std::shared_ptr<IValue>	makeFloat(double def);
	static inline std::shared_ptr<IValue>	makeFloat(void);
	static inline std::shared_ptr<IValue>	makeString(std::string &&def);
	static inline std::shared_ptr<IValue>	makeString(void);
	static inline std::shared_ptr<IValue>	noArg();

	inline void	setOptions(std::initializer_list<OptionsCont> &&in);

	inline std::shared_ptr<IValue> &operator[](const std::string &name) {
		auto it = _longRef.find(name);

		if (it != _longRef.end())
			return (*it).second;
		else
			throw std::runtime_error((std::string("Cannot find ") + name).c_str());
	}

	inline std::shared_ptr<IValue> &operator[](const char name) {
		auto it = _shortRef.find(name);

		if (it != _shortRef.end())
			return (*it).second;
		else
			throw std::runtime_error((std::string("Cannot find ") + name).c_str());
	}

	void	parse(void);

	void	setUsage(std::string &&title, std::string &&body)
		{ _usageTitle = title; _usageBody = body; }
	void	setArgsTitle(std::string &&title) { _argsTitle = title; }

	friend	std::ostream	&operator<<(std::ostream &to, Opts const &me);
private:
	int	_ac;
	char	**_av;

	std::string	_usageTitle;
	std::string	_usageBody;

	std::string	_argsTitle;

	int		_biggestName = 0;

	std::map<const std::string, std::shared_ptr<IValue>>
		_longRef;
	std::map<const char, std::shared_ptr<IValue>>
		_shortRef;
	std::list<std::shared_ptr<IValue>>	_vals;
};

struct Opts::OptionsCont {
public:
	std::string		lName;
	char			sName = 0;
	std::shared_ptr<IValue>	value;
	std::string		strHelp;
	std::string		strError;
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

	inline void	setStrError(std::string const &strE) { _strError = strE; }
	inline void	setStrHelp(std::string const &strH) { _strHelp = strH; }
	inline void	setHelpName(std::string const &strHelpName) { _helpName = strHelpName; }
	inline void	setBiggestNamePtr(int *ptr) { _biggestNamePtr = ptr; }
	inline void	incCounter(void) { _count++; }
	inline int	count(void) const { return _count; }

	friend	std::ostream	&operator<<(std::ostream &to, IValue const &me);
protected:
	std::string	_strError;
	std::string	_strHelp;
	std::string	_helpName;
	std::string	_def;
	int 		*_biggestNamePtr;
	int 		_count = 0;
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

	inline Int	*setDefault(type in) { _def = std::to_string(in); return this; }
	inline type	get(void) { return _val; }
	virtual void	parse(std::string const &in) final { _val = std::stol(in); }
private:
	long		_val;
};

class Opts::String : public Opts::IValue {
public:
	using	type = std::string&;
	String(type defVal): IValue(false), _val(defVal) {}

	inline String	*setDefault(type in) { _def = "\"" + in + "\""; return this; }
	inline type	get(void) { return _val; }
	virtual void	parse(std::string const &in) final { _val = in; }
private:
	std::string	_val;
};

class Opts::Float : public Opts::IValue {
public:
	using type = double;
	Float(type defVal): IValue(false), _val(defVal) {}

	inline Float	*setDefault(type in) { _def = std::to_string(in); return this; }
	inline type	get(void) { return _val; }
	virtual void	parse(std::string const &in) final { _val = std::stod(in); }
private:
	double		_val;
};

inline void	Opts::setOptions(std::initializer_list<OptionsCont> &&in) {
	for (auto &i: in) {
		std::string	strHelpName("");
		if (i.strError.empty() == false)
			i.value->setStrError(i.strError);
		if (i.strHelp.empty() == false)
			i.value->setStrHelp(i.strHelp);

		if (i.lName.size() != 0) {
			strHelpName += std::string("--") + i.lName;
			_longRef[i.lName] = i.value;
		}
		if (i.sName != 0) {
			strHelpName += (strHelpName.empty()
						? "" : ", ") +
					std::string("-") + i.sName;
			_shortRef[i.sName] = i.value;
		}
                if (strHelpName.size() > (std::size_t) _biggestName)
			_biggestName = strHelpName.size();
		i.value->setHelpName(strHelpName);
		i.value->setBiggestNamePtr(&_biggestName);
		_vals.push_back(i.value);
	}
}

inline std::shared_ptr<Opts::IValue>	Opts::makeInt(long def) {
	return std::shared_ptr<IValue>(reinterpret_cast<IValue*>((new Int(def))->setDefault(def)));
}

inline std::shared_ptr<Opts::IValue>	Opts::makeInt(void) {
	return std::shared_ptr<IValue>(reinterpret_cast<IValue*>(new Int(0)));
}

inline std::shared_ptr<Opts::IValue>	Opts::makeFloat(double def) {
	return std::shared_ptr<IValue>(reinterpret_cast<IValue*>((new Float(def))->setDefault(def)));
}

inline std::shared_ptr<Opts::IValue>	Opts::makeFloat(void) {
	return std::shared_ptr<IValue>(reinterpret_cast<IValue*>(new Float(0.0)));
}

inline std::shared_ptr<Opts::IValue>	Opts::makeString(std::string &&def) {
	return std::shared_ptr<IValue>(reinterpret_cast<IValue*>((new String(def))->setDefault(def)));
}

inline std::shared_ptr<Opts::IValue>	Opts::makeString(void) {
	std::string	arg("");
	return std::shared_ptr<IValue>(reinterpret_cast<IValue*>(new String(arg)));
}

inline std::shared_ptr<Opts::IValue>	Opts::noArg() {
	return std::shared_ptr<IValue>(reinterpret_cast<IValue*>(new NoValue()));
}

}
