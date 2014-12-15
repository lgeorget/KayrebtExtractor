#include <iostream>
#include <string>
#include <gcc-plugin.h>
#include <tree.h>
#include "string_cst.h"
#include "value.h"
#include "bad_tree_exception.h"

StringCst::StringCst(tree t) : Value()
{
	if (TREE_CODE(t) != STRING_CST)
		throw BadTreeException(t, "string_cst");

	_length = TREE_STRING_LENGTH(t) - 1;
	_content = TREE_STRING_POINTER(t);
}

std::string StringCst::print() const
{
	return std::string(_content, _length);
}
