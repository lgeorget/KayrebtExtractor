#ifndef CONFIGURATOR_H
#define CONFIGURATOR_H

#include <cstdlib>
#include <iostream>
#include <functional>
#include <iterator>
#include <vector>
#include <map>
#include <regex>
#include "url_finder.h"

class Configurator
{
	private:
		std::vector<std::string> _functions;
		std::map<unsigned int, std::string> _categoriesRepresentation;
		std::vector<std::pair<std::regex,unsigned int>> _categoryBeginning;
		std::vector<std::regex> _categoryEnding;
		std::vector<std::pair<std::regex, unsigned int>> _categoryStandalone;
		bool _greedymode = false;
		std::string _dbFile;
		std::string _dbName;

		class CategoryDumper {
			private:
				const Configurator& _parent;

			public:
				CategoryDumper(const Configurator& parent);
				std::string operator()(unsigned int i);
		};
		CategoryDumper _catdump;
		std::reference_wrapper<CategoryDumper> _refcatdump;

		class Categorizer {
			private:
				const Configurator& _parent;
				unsigned int _currentCategory = 0;
				bool _persistent = false;

			public:
				Categorizer(const Configurator& parent);
				unsigned int operator()(const std::string& content);
		};
		Categorizer _categorizer;
		std::reference_wrapper<Categorizer> _refcategorizer;

	public:
		Configurator(std::string config, std::string source);
		bool mustGraph(std::string functionName) const;
		bool shallDumpUrls() const;
		std::function<std::string(unsigned int)> getCategoryDumper() const;
		std::function<unsigned int(std::string)> getCategorizer() const;
		const std::string& getDbFile() const;
		const std::string& getDbName() const;
};

#endif
