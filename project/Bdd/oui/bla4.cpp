
#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <unordered_map>
#include <memory>

#include "BddData.h"

namespace bdd {

class Bdd { /* à plusieurs Table. ex: bdd["sushi"] ou bdd["vehicule"] */
private:

	class Table {/* à plusieurs Element. ex: bdd["sushi"][0] ou bdd["vehicule"][1] */
	private:

		class Element { /* à plusieurs data. ex: bdd["sushi"][0]["riz"] ou bdd["vehicule"][0]["nb_roue"] */
		public:
			Element(std::unordered_map<std::string, Data::Type> &description): _description{description} {}

			Data &operator[](std::string const &data_name)
			{
				if (_description.find(data_name) == _description.end())
					throw std::runtime_error{"get data : bad name of data"};
				if (_datas.find(data_name) == _datas.end())
					_datas.emplace(data_name, _description.at(data_name));
				return _datas.at(data_name);
			}

			friend std::ostream &operator<<(std::ostream &os, Element const &element)
			{
				os << "{\n";
				bool first = true;
				for (auto const &e : element._datas) {
					if (first == false)
						os << ",\n";
					else
						first = false;
					switch (element._description[e.first]) {
						case Data::Type::Number:
							os << "    \"" << e.first << "\": " << e.second.to<Data::Number>();
							break;
						case Data::Type::Float:
							os << "    \"" << e.first << "\": " << e.second.to<Data::Float>();
							break;
						case Data::Type::String:
							os << "    \"" << e.first << "\": \"" << e.second.to<Data::String>() << "\"";
							break;
						// case Data::Type::Date:
						// 	os << "    \"" << e.first << "\": " << asctime(localtime(&e.second.to<Data::Date>()));
						// 	break;
					}
				}
				return os << "\n  }";
			}

		private:
			std::unordered_map<std::string, Data::Type>	&_description;
			std::unordered_map<std::string, Data>		_datas; /* peut être soit number, soit string, soit date */
		}; /* class Element */

	public:
		Table(Bdd &bdd): _bdd{bdd} {}

		void setDescription(std::string const &data_name, Data::Type type)
		{
			if (_description.find(data_name) != _description.end())
				throw std::runtime_error{"DataType already set"};
			_description[data_name] = type;
		}

		size_t newElement()
		{
			_elements.push_back({_description});
			return _elements.size() - 1;
		}

		Element &operator[](size_t key) /* get un element */
		{
			return _elements.at(key);
		}

		friend std::ostream &operator<<(std::ostream &os, Table const &champ)
		{
			os << "{\n";
			bool first = true;
			for (auto i = 0; i < champ._elements.size(); ++i) {
				if (first == false)
					os << ",\n";
				else
					first = false;
				os << "  " << i << ": " << champ._elements[i];

			}
			return os << "\n}";
		}

	private:
		Bdd						&_bdd;
		std::unordered_map<std::string, Data::Type>		_description;
		std::vector<Element>				_elements;
	}; /* class Table */

public:

	Table &operator[](std::string const &champ_name)
	{
		if (_champs.find(champ_name) == _champs.end()) {
			_champs.emplace(champ_name, Table{*this});
		}
		return _champs.at(champ_name);
	}

	friend std::ostream &operator<<(std::ostream &os, Bdd const &bdd)
	{
		for (auto const &e : bdd._champs)
			os << "\"" << e.first << "\": " << e.second << "\n";
		return os;
	}

private:
	std::unordered_map<std::string, Table>	_champs;
}; /* class Bdd */

}

int main()
{
	bdd::Bdd bdd;

	bdd["sushi"].setDescription("repas", bdd::Data::Type::String);
	bdd["sushi"].setDescription("temps", bdd::Data::Type::Float);
	bdd["sushi"].setDescription("riz", bdd::Data::Type::Number);
	bdd["sushi"].setDescription("saumon", bdd::Data::Type::Number);

	auto e1 = bdd["sushi"].newElement();
	auto e2 = bdd["sushi"].newElement();
	bdd["sushi"][e1]["riz"] = 42;
	bdd["sushi"][e1]["saumon"] = 12;
	bdd["sushi"][e2]["riz"] = 42;
	bdd["sushi"][e2]["saumon"] = 12;
	bdd["sushi"][e2]["repas"] = "midi";
	bdd["sushi"][e2]["temps"] = 30.5;

	std::cout << bdd;
}