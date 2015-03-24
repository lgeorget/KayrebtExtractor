#include <iostream>
#include <functional>
#include <iterator>
#include <vector>
#include <map>
#include <regex>

class Configurator
{
	private:
		std::vector<std::string> _functions;
		std::map<unsigned int, std::string> _categoriesRepresentation;
		std::vector<std::pair<std::regex,unsigned int>> _categoryBeginning;
		std::vector<std::regex> _categoryEnding;
		std::vector<std::pair<std::regex, unsigned int>> _categoryStandalone;
		bool _greedymode = false;

		class CategoryDumper {
			public:
				CategoryDumper(const Configurator& parent);
				std::string operator()(unsigned int i);
			private:
				const Configurator& _parent;
		};
		std::function<std::string(unsigned int)> _catdump;

		class Categorizer {
			private:
				const Configurator& _parent;
				unsigned int _currentCategory = 0;
				bool _persistent = false;

			public:
				Categorizer(const Configurator& parent);
				unsigned int operator()(std::string content);
		};
		std::function<unsigned int(std::string)> _categorizer;

	public:
		Configurator(std::string config, std::string source);
		bool mustGraph(std::string functionName);
		const std::function<std::string(unsigned int)>& getCategoryDumper();
		const std::function<unsigned int(std::string)>& getCategorizer();
};
