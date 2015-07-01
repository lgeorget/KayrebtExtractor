/**
 * \file constructor.h
 * \author Laurent Georget
 * \date 2015-03-03
 * \brief Definition of a structure initializer
 */
#ifndef CONSTRUCTOR_H
#define CONSTRUCTOR_H

#include <iostream>
#include <string>
#include <vector>
#include <memory>
#include <gcc-plugin.h>
#include <tree.h>
#include "value.h"

/**
 * \brief Represent a structure initializer
 */
class Constructor : public Value
{
	public:
		/**
		 * \brief Construct a new Constructor from a TREE CONSTRUCTOR
		 * \param t the tree
		 */
		explicit Constructor(tree t);
		std::string print() const override;

	private:
		/** The fields of the structure */
		std::vector<std::shared_ptr<Value>> _fields;
		/** A textual representation of the constructor for dumping purposes */
		std::string _built_str;
};

#endif
