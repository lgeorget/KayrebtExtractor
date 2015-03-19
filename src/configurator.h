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

		class CategoryDumper {
			public:
				CategoryDumper(const Configurator& parent) : _parent(parent) {}
				std::string operator()(unsigned int i) {
					return _parent._categoriesRepresentation.at(i);
				}
			private:
				const Configurator& _parent;
		};
		std::function<std::string(unsigned int)> _catdump;

		class Categorizer {
			private:
				const Configurator& _parent;
				unsigned int _currentCategory;
				bool _persistent;

			public:
				Categorizer(const Configurator& parent) : _parent(parent) {}
				unsigned int operator()(std::string content) {
#ifndef NDEBUG
					std::cerr << "CategoryStandalone size: " << _parent._categoryStandalone.size() << std::endl;
#endif
					if (_persistent) {
						bool foundEnding = false;
						unsigned int i;
						for (i=0 ; i<_parent._categoryEnding.size() && !foundEnding ; i++) {
							foundEnding = std::regex_match(content, _parent._categoryEnding[i]);
						}
						if (foundEnding) { //end of category region
							unsigned int oldCat = _currentCategory; // the current node is part of the category
							_currentCategory = 0; // ...but the next will not
							_persistent = false;
							return oldCat;
						} else { //still in category region
							return _currentCategory; //no support for nested regions nor standalone categories inside regions
						}
					}
					bool foundBeginning = false;
					unsigned int i;
					for (i=0 ; i<_parent._categoryBeginning.size() && !foundBeginning ; i++) {
						foundBeginning = std::regex_match(content, _parent._categoryBeginning[i].first);
					}
					if (foundBeginning) {
						_currentCategory = _parent._categoryBeginning[i-1].second;
						_persistent = true;
						return _currentCategory; //beginning of regions have precedence over standalone nodes
					}

					bool foundStandalone = false;
					for (i=0 ; i<_parent._categoryStandalone.size() && !foundStandalone ; i++) {
#ifndef NDEBUG
						std::cerr << "Matching \'" << content << "\': ";
#endif
						foundStandalone = std::regex_match(content, _parent._categoryStandalone[i].first);
#ifndef NDEBUG
						std::cerr << std::boolalpha << foundStandalone << std::endl;
#endif
					}
					if (foundStandalone) {
						if (_parent._categoriesRepresentation.count(_parent._categoryStandalone[i-1].second) == 0) {
							std::cerr << "WARNING: discarded undefined category " << _parent._categoryStandalone[i-1].second << std::endl;
							_currentCategory = 0;
						} else {
							_currentCategory = _parent._categoryStandalone[i-1].second;
						}
					} else {
						_currentCategory = 0;
					}

					return _currentCategory;
				}
		};
		std::function<unsigned int(std::string)> _categorizer;

	public:
		Configurator(std::string config, std::string source);
		bool mustGraph(std::string functionName);
		const std::function<std::string(unsigned int)>& getCategoryDumper();
		const std::function<unsigned int(std::string)>& getCategorizer();
};
