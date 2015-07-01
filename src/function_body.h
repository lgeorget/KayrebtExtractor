/**
 * \file function_body.h
 * \author Laurent Georget
 * \date 2015-03-03
 * \brief Definition of a function composed of basic blocks
 */
#ifndef FUNCTION_BODY_H
#define FUNCTION_BODY_H

#include <iostream>
#include <vector>
#include <memory>
#include <gcc-plugin.h>
#include <tree.h>
#include <gimple.h>
#include <function.h>
#include "expression.h"

class Dumper;

/**
 * \brief Represent the body of a function, composed of basic blocks consisting
 * of sequences of statements
 */
class FunctionBody
{
	public:
		/**
		 * \brief Construct a FunctionBody from a GCC function structure
		 * \param t the function
		 */
		explicit FunctionBody(function* t);
		/**
		 * \brief Visit method for dumpers
		 * \param d the visiting dumper
		 */
		void accept(Dumper& d);

	private:
		/** The list of basic blocks with their function */
		std::vector<std::pair<basic_block,std::vector<std::shared_ptr<Expression>>>> _bb;
		/** The function */
		function* _fn;

	friend class ActivityGraphDumper;
};

#endif

