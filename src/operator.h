/**
 * \file operator.h
 * \author Laurent Georget
 * \date 2015-03-03
 * \brief Definition of an abstract operator
 */
#ifndef OPERATOR_H
#define OPERATOR_H

#include <iostream>
#include <map>
#include <gcc-plugin.h>
#include <tree.h>

/**
 * \brief Static tool box to manipulate a wide range of operators
 */
class Operator
{
	public:
		/**
		 * \brief Give the textual representation of the operator
		 * used in an operation described by a GCC TREE
		 *
		 * For example, the tree ADDITION would give the operator '+',
		 * the tree BINARY AND would give '&', the LOGICAL AND '&&', etc.
		 * \param op the tree
		 * \return the textual representation of the operator used in
		 * \a op
		 */
		static const std::string& print(tree_code op);

	private:
		/** Deleted constructor for the static class Operator */
		Operator() = delete;
		/** Mapping between the tree codes and the operators corresponding
		 * to them*/
		const static std::map<tree_code,std::string> symbols;
};

#endif
