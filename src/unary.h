/**
 * \file unary.h
 * \author Laurent Georget
 * \date 2015-03-03
 * \brief Definition of an abstract unary operation application
 */
#ifndef UNARY_H
#define UNARY_H

#include <iostream>
#include <memory>
#include <gcc-plugin.h>
#include <tree.h>
#include "value.h"

/**
 * \brief Represent the application of a unary operator to some operand
 */
class Unary : public Value
{
	public:
		/**
		 * \brief Construct a new Unary from a GCC TREE and an operator
		 * symbol
		 * \param t the tree, which must represent a unary operator
		 * applied to an operand
		 * \param symbol the textual representation of the operator
		 * ('&', '*', etc.)
		 */
		explicit Unary(tree t, const std::string& symbol);
		std::string print() const override;

	private:
		/** The operand */
		std::shared_ptr<Value> _inside;
		/** Theoperator symbol */
		const std::string _symbol;
};

#endif
