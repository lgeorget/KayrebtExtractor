/**
 * \file integer_cst.h
 * \author Laurent Georget
 * \date 2015-03-03
 * \brief Definition of an integer constant
 */
#ifndef INTEGER_CST_H
#define INTEGER_CST_H

#include <iostream>
#include <string>
#include <gcc-plugin.h>
#include <tree.h>
#include "value.h"

/**
 * \brief Represent a numerical integer constant
 */
class IntegerCst : public Value
{
	public:
		/**
		 * \brief Construct a new IntegerCst from a TREE INTEGER_CST
		 * structure
		 * \param t the tree
		 */
		explicit IntegerCst(tree t);
		std::string print() const override;

	private:
		/** The value of the constant */
		int _integ;
};

#endif
