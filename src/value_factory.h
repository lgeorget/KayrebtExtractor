/**
 * \file value_factory.h
 * \author Laurent Georget
 * \date 2015-03-03
 * \brief Definition of the Value Factory
 */
#ifndef VALUE_FACTORY_H
#define VALUE_FACTORY_H

#include <memory>
#include <map>
#include <gcc-plugin.h>

class Value;

/**
 * \brief Singleton used to build values from GCC tree structures
 */
class ValueFactory
{
	private:
		/** Build the factory, this is private because there can
		 * be only one instance of the factory */
		ValueFactory() = default;

	public:
		/** The public instance available to the world */
		static ValueFactory INSTANCE;
		/**
		 * \brief Build a Value from a GCC TREE structure
		 * \param t the tree structure
		 * \return the Value built
		 */
		std::shared_ptr<Value> build(tree t);
		/** A memoization map for string constant */
		std::map<tree,std::shared_ptr<Value>> strings;
		/** A memoization map for integer constants */
		std::map<tree,std::shared_ptr<Value>> integers;
		/** A memoization map for identifiers */
		std::map<tree,std::shared_ptr<Value>> idents;
		/** A memoization map for ssa names */
		std::map<tree,std::shared_ptr<Value>> ssas;
};

#endif
