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
		if (match.IsMap()) {
			for (YAML::const_iterator it=start_match.begin();it!=start_match.end();++it) {
				_categoryBeginning.push_back(std::make_pair(std::regex(it->first.as<std::string>()),it->second.as<unsigned int>()));
			}
		}
		YAML::Node end_match = sourceConf["end_match"];
		if (match.IsMap()) {
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
		if (match.IsMap()) {
			for (YAML::const_iterator it=start_match.begin();it!=start_match.end();++it) {
				_categoryBeginning.push_back(std::make_pair(std::regex(it->first.as<std::string>()),it->second.as<unsigned int>()));
			}
		}
		YAML::Node end_match = generalConf["end_match"];
		if (match.IsMap()) {
			for (YAML::const_iterator it=end_match.begin();it!=end_match.end();++it) {
				_categoryEnding.push_back(std::regex(it->as<std::string>()));
			}
		}
	}
#ifndef NDEBUG
	std::cerr << "Categories representations: " << std::endl;
	for (auto categ : _categoriesRepresentation)
		std::cerr << categ.first << ": " << categ.second << std::endl;
#endif
}

bool Configurator::mustGraph(std::string functionName)
{
#ifndef NDEBUG
	std::cerr << "Asking for function " << functionName << std::endl;
	std::cerr << "List of functions: [";
	std::copy(_functions.begin(), _functions.end(), std::ostream_iterator<std::string>(std::cerr, ", "));
	std::cerr << "]" << std::endl;
#endif
	return std::find(_functions.begin(), _functions.end(), functionName) != _functions.end();
}

const std::function<std::string(unsigned int)>& Configurator::getCategoryDumper() {
			return _catdump;
		}

const std::function<unsigned int(std::string)>& Configurator::getCategorizer() {
			return _categorizer;
		}
