/**
 * \file array_ref.h
 * \author Laurent Georget
 * \date 2015-03-03
 * \brief Definition of an indirection inside an array
 */
#ifndef ARRAY_REF_H
#define ARRAY_REF_H

#include <iostream>
#include <string>
#include <memory>
#include <gcc-plugin.h>
#include <tree.h>
#include "value.h"

/**
 * \brief Represent an indirection in an array
 */
class ArrayRef : public Value
{
	public:
		/**
		 * \brief Construct a new ArrayRef from a GCC tree expression
		 * \param t the tree
		 */
		explicit ArrayRef(tree t);
		std::string print() const override;

	private:
		std::shared_ptr<Value> _array; /*!< The array */
		std::shared_ptr<Value> _index; /*!< The index in the array */
};

#endif
