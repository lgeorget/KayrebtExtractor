/**
 * \file integer_cst.cpp
 * \author Laurent Georget
 * \date 2015-03-03
 * \brief Implementation of the IntegerCst
 */
#include <iostream>
#include <string>
#include <gcc-plugin.h>
#include <tree.h>
#include "integer_cst.h"
#include "value.h"
#include "bad_tree_exception.h"

IntegerCst::IntegerCst(tree t) : Value(t)
{
	if (TREE_CODE(t) != INTEGER_CST)
		throw BadTreeException(t, "integer_cst");

	_integ = (TREE_INT_CST_HIGH(t) << 32)
	       + TREE_INT_CST_LOW(t);
}

std::string IntegerCst::print() const
{
	return std::to_string(_integ);
}
