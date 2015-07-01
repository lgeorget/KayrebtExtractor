/**
 * \file string_cst.h
 * \author Laurent Georget
 * \date 2015-03-03
 * \brief Definition of a string constant
 */
#ifndef STRING_CST_H
#define STRING_CST_H

#include <iostream>
#include <string>
#include <gcc-plugin.h>
#include <tree.h>
#include "value.h"

/**
 * \brief Represent a static string constant
 */
class StringCst : public Value
{
	public:
		/**
		 * \brief Construct a new StringCst from a GCC TREE CST value
		 * \param t the tree
		 */
		StringCst(tree t);
		std::string print() const override;

	private:
		/** The textual representation for the string constant, for
		 * dumping purpose */
		std::string _built_str;
};

#endif
