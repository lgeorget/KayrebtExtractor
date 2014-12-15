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
	std::cerr << _integ << std::endl;
}

std::string IntegerCst::print() const
{
	return std::to_string(_integ);
}
