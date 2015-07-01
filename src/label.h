/**
 * \file label.h
 * \author Laurent Georget
 * \date 2015-03-03
 * \brief Definition of a flow control label
 */
#ifndef LABEL_H
#define LABEL_H

#include <iostream>
#include <gcc-plugin.h>
#include <tree.h>
#include "value.h"

/**
 * \brief Represent a label for a jump
 */
class Label : public Value
{
	public:
		/**
		 * \brief Construct a new Label from a GCC TREE LABEL
		 * \param t the tree
		 */
		explicit Label(tree t);
		virtual std::string print() const;
};

#endif
