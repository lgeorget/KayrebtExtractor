/**
 * \file configurator.h
 * \author Laurent Georget
 * \date 2015-10-18
 * \brief Definition of the configuration parser
 */
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

/**
 * \brief Parse and interpret the configuration file
 */
class Configurator
{
	private:
		/**
		 * \brief The list of functions to dump as activity diagrams
		 */
		std::vector<std::string> _functions;
		/**
		 * \brief Map each category to the string to add in the
		 * attribute section of the objects of this category
		 */
		std::map<unsigned int, std::string> _categoriesRepresentation;
		/**
		 * \brief A set of regexes identifying the beginning of a
		 * category
		 *
		 * From the node whose label the regex to the node whose label
		 * match a regex in \a _categoryEnding, all nodes reachable
		 * from the former will be in the specified category.
		 * \see _categoryEnding
		 */
		std::vector<std::pair<std::regex,unsigned int>> _categoryBeginning;
		/**
		 * \brief A set of regexes which identify the end of
		 * categories
		 * \see _categoryBeginning
		 */
		std::vector<std::regex> _categoryEnding;
		/**
		 * \brief A set of regexes identifying nodes which must be bound
		 * to a category
		 *
		 * Standalone categories have precedence over categories defined
		 * in \a _categoryBeginning
		 */
		std::vector<std::pair<std::regex, unsigned int>> _categoryStandalone;
		/**
		 * \brief Tell whether all met functions should be dumped
		 */
		bool _greedymode = false;
		/**
		 * \brief The SQLITE3 file containing the database of function
		 * symbols, to dump line and file information in the diagrams
		 */
		std::string _dbFile;
		/**
		 * \brief The name of the database of function symbols
		 * \see _dbFile
		 */
		std::string _dbName;

		/**
		 * \brief Functor which outputs for a category the corresponding
		 * string of attributes
		 */
		class CategoryDumper {
			private:
				/**
				 * \brief The configurator the CategoryDumper
				 * refers to
				 */
				const Configurator& _parent;

			public:
				/**
				 * \brief Dummy constructor for the
				 * \a CategoryDumper
				 *
				 * A \a CategoryDumper instance is built only by
				 * its ``parent'', the \a Configurator
				 */
				CategoryDumper(const Configurator& parent);
				/**
				 * \brief Output the string of attributes of a
				 * given category
				 *
				 * \param i the category
				 *
				 * \return the string to add to nodes of the
				 * given category
				 */
				std::string operator()(unsigned int i);
		};
		/**
		 * \brief An instance of the \a CategoryDumper
		 */
		CategoryDumper _catdump;
		/**
		 * \brief A reference to \a _catdump, for export
		 */
		std::reference_wrapper<CategoryDumper> _refcatdump;

		/**
		 * \brief Functor which outputs the category of a node given as
		 * a parameter
		 *
		 * This functor maintains internal state because some categories
		 * applies to series of nodes.
		 */
		class Categorizer {
			private:
				/**
				 * \brief The configurator the Categorizer
				 * refers to
				 */
				const Configurator& _parent;
				/**
				 * \brief The category of the current branch of
				 * nodes (if a category has started and not
				 * ended yet)
				 */
				unsigned int _currentCategory = 0;
				/**
				 * \brief Tell whether the current category
				 * applis fot future nodes
				 */
				bool _persistent = false;

			public:
				/**
				 * \brief Dummy constructor, called from \a
				 * Configurator::Configurator()
				 */
				Categorizer(const Configurator& parent);
				/**
				 * \brief Output a category given the label of
				 * a node
				 *
				 * \param content The label of the node to
				 * categorize
				 *
				 * \return A categry number, 0 means ``no
				 * category''
				 */
				unsigned int operator()(const std::string& content);
		};
		/**
		 * \brief An instance of \a Categorizer
		 */
		Categorizer _categorizer;
		/**
		 * \brief A reference to \a _categorizer, for export
		 */
		std::reference_wrapper<Categorizer> _refcategorizer;

	public:
		/**
		 * \brief Constructor for \a Configurator
		 *
		 * \param config the name of the configuration file
		 * \param source the name of the compilation unit under analysis
		 */
		Configurator(std::string config, std::string source);
		/**
		 * \brief Tell whether a given function must be dumped as a
		 * diagram
		 *
		 * \param functionName the undecorated base name of the function
		 *
		 * \return true if, and only if, an activity diagram must be
		 * dumped for the function
		 */
		bool mustGraph(std::string functionName) const;
		/**
		 * \brief Tell whether the program will be able to enrich the
		 * diagram with URLs
		 *
		 * The URLs references the point where a function is defined in
		 * nodes representing function calls.
		 * Note that the validity of the database path and name is not
		 * checked here.
		 *
		 * \return true if, and only if, a database of function symbols
		 * was configured
		 */
		bool shallDumpUrls() const;
		/**
		 * \brief Give a reference to an instance of \a CategoryDumper
		 *
		 * \return a category dumper for the current configuration
		 */
		std::function<std::string(unsigned int)> getCategoryDumper() const;
		/**
		 * \brief Give a reference to an instance of \a Categorizer
		 *
		 * \return a categorizer for the current configuration
		 */
		std::function<unsigned int(std::string)> getCategorizer() const;
		/**
		 * \brief Give the path to the database of symbols
		 *
		 * \return the path to the database of symbols, or an empty
		 * string if no such database has been configured
		 */
		const std::string& getDbFile() const;
		/**
		 * \brief Give the name of the database of symbols
		 *
		 * \return the name of the database of symbols, or an empty
		 * string if no such database has been configured
		 */
		const std::string& getDbName() const;
};

#endif
