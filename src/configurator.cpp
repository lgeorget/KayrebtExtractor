#include <iostream>
#include <functional>
#include <algorithm>
#include <iterator>
#include <vector>
#include <map>
#include <yaml.h>
#include "configurator.h"

Configurator::Configurator(std::string config, std::string source) : _catdump(CategoryDumper(*this)), _categorizer(Categorizer(*this))
{
#ifndef NDEBUG
	std::cerr << "Building configuration for " << source << std::endl;
#endif
	YAML::Node conf = YAML::LoadFile(config);

	YAML::Node sourceConf = conf[source];
	if (sourceConf) {
#ifndef NDEBUG
		std::cerr << "Found section \'" << source << "\'" << std::endl;
#endif
		YAML::Node functions = sourceConf["functions"];
		YAML::Node categories = sourceConf["functions"];
		if (functions.IsScalar()) {
			_functions.push_back(functions.as<std::string>());
		} else if (functions.IsSequence()) {
			for (YAML::const_iterator it=functions.begin();it!=functions.end();++it) {
				_functions.push_back(it->as<std::string>());
			}
		}

		if (categories.IsMap()) {
			for (YAML::const_iterator it=categories.begin();it!=categories.end();++it) {
				_categoriesRepresentation[it->first.as<unsigned int>()] = it->second.as<std::string>();
			}
		}

		YAML::Node match = sourceConf["match"];
		if (match.IsMap()) {
			for (YAML::const_iterator it=match.begin();it!=match.end();++it) {
				_categoryStandalone.push_back(std::make_pair(std::regex(it->first.as<std::string>()),it->second.as<unsigned int>()));
			}
		}
		YAML::Node start_match = sourceConf["start_match"];
		if (start_match.IsMap()) {
			for (YAML::const_iterator it=start_match.begin();it!=start_match.end();++it) {
				_categoryBeginning.push_back(std::make_pair(std::regex(it->first.as<std::string>()),it->second.as<unsigned int>()));
			}
		}
		YAML::Node end_match = sourceConf["end_match"];
		if (end_match.IsSequence()) {
			for (YAML::const_iterator it=end_match.begin();it!=end_match.end();++it) {
				_categoryEnding.push_back(std::regex(it->as<std::string>()));
			}
		}
	}

	YAML::Node generalConf = conf["general"];
	if (generalConf) {
#ifndef NDEBUG
	std::cerr << "Found section 'general'" << std::endl;
#endif
		YAML::Node functions = generalConf["functions"];
		YAML::Node categories = generalConf["categories"];
		if (functions.IsScalar()) {
			_functions.push_back(functions.as<std::string>());
		} else if (functions.IsSequence()) {
			for (YAML::const_iterator it=functions.begin();it!=functions.end();++it) {
				_functions.push_back(it->as<std::string>());
			}
		}

		if (categories.IsMap()) {
			for (YAML::const_iterator it=categories.begin();it!=categories.end();++it) {
				//do not overwrite existing categories
				_categoriesRepresentation.insert(std::make_pair(it->first.as<unsigned int>(), it->second.as<std::string>()));
			}
		}

		YAML::Node match = generalConf["match"];
		if (match.IsMap()) {
			for (YAML::const_iterator it=match.begin();it!=match.end();++it) {
				_categoryStandalone.push_back(std::make_pair(std::regex(it->first.as<std::string>()),it->second.as<unsigned int>()));
			}
		}
		YAML::Node start_match = generalConf["start_match"];
		if (start_match.IsMap()) {
			for (YAML::const_iterator it=start_match.begin();it!=start_match.end();++it) {
				_categoryBeginning.push_back(std::make_pair(std::regex(it->first.as<std::string>()),it->second.as<unsigned int>()));
			}
		}
		YAML::Node end_match = generalConf["end_match"];
		if (end_match.IsSequence()) {
			for (YAML::const_iterator it=end_match.begin();it!=end_match.end();++it) {
				_categoryEnding.push_back(std::regex(it->as<std::string>()));
			}
		}

		YAML::Node greedy = generalConf["greedy"];
		if (greedy.IsScalar() && greedy.as<int>() != 0)
			_greedymode = true;
	}
#ifndef NDEBUG
	std::cerr << "Categories representations: " << std::endl;
	for (auto categ : _categoriesRepresentation)
		std::cerr << categ.first << ": " << categ.second << std::endl;
#endif
}

bool Configurator::mustGraph(std::string functionName)
{
	if (_greedymode)
		return true;

#ifndef NDEBUG
	std::cerr << "Asking for function " << functionName << std::endl;
	std::cerr << "List of functions: [";
	std::copy(_functions.begin(), _functions.end(), std::ostream_iterator<std::string>(std::cerr, ", "));
	std::cerr << "]" << std::endl;
#endif
	return std::find(_functions.begin(), _functions.end(), functionName) != _functions.end();
}

const std::function<std::string(unsigned int)>& Configurator::getCategoryDumper()
{
	return _catdump;
}

const std::function<unsigned int(std::string)>& Configurator::getCategorizer()
{
	return _categorizer;
}

Configurator::CategoryDumper::CategoryDumper(const Configurator& parent) : _parent(parent)
{}

std::string Configurator::CategoryDumper::operator()(unsigned int i)
{
	return _parent._categoriesRepresentation.at(i);
}

Configurator::Categorizer::Categorizer(const Configurator& parent) : _parent(parent)
{}

unsigned int Configurator::Categorizer::operator()(std::string content)
{
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

