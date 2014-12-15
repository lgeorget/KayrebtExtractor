#include <iostream>
#include <string>
#include <gcc-plugin.h>
#include <tree.h>
#include "string_cst.h"
#include "value.h"
#include "bad_tree_exception.h"

StringCst::StringCst(tree t) : Value(t)
{
	if (TREE_CODE(t) != STRING_CST)
		throw BadTreeException(t, "string_cst");

	int length = TREE_STRING_LENGTH(t) - 1;
	const char* content = TREE_STRING_POINTER(t);

	_built_str =  "\"" + std::string(content, length) + "\"";
}

std::string StringCst::print() const
{
	return _built_str;
}
