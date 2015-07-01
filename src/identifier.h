/**
 * \file identifier.h
 * \author Laurent Georget
 * \date 2015-03-03
 * \brief Definition of a name symbol
 */
#ifndef IDENTIFIER_H
#define IDENTIFIER_H

#include <gcc-plugin.h>
#include <tree.h>
#include "value.h"

/**
 * \brief Represent a symbol identifying a variable, a function, etc.
 */
class Identifier : public Value
{
	public:
		/**
		 * \brief Construct an Identifier from a GCC TREE IDENTIFIER
		 * structure
		 * \param t the tree identifier structure
		 */
		explicit Identifier(tree t);
		std::string print() const override;

	private:
		/** The value of the identifier, i.e., the name of the object
		 * identified*/
		std::string _name;
		/** A counter to give an alomost unique name to anonymous objects */
		static unsigned int counter;
};

#endif
