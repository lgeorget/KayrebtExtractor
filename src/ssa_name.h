/**
 * \file ssa_name.h
 * \author Laurent Georget
 * \date 2015-11-16
 * \brief Definition of a ssa name symbol
 */
#ifndef SSA_NAME_H
#define SSA_NAME_H

#include <gcc-plugin.h>
#include <tree.h>
#include "value.h"

/**
 * \brief Represent a symbol identifying a variable, a function, etc.
 */
class SsaName : public Value
{
	public:
		/**
		 * \brief Construct an Identifier from a GCC TREE IDENTIFIER
		 * structure
		 * \param t the tree identifier structure
		 */
		explicit SsaName(tree t);
		std::string print() const override;

	private:
		/** The value of the identifier, i.e., the name of the object
		 * identified*/
		std::string _name;
		/** A counter to give an almost unique name to anonymous objects */
		static unsigned int counter;
};

#endif
