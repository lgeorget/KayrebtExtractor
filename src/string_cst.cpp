#include <iostream>
#include <algorithm>
#include <string>
#include <gcc-plugin.h>
#include <tree.h>
#include "string_cst.h"
#include "value.h"
#include "bad_gimple_exception.h"

StringCst::StringCst(tree t) : Value(t)
{
	if (TREE_CODE(t) != STRING_CST)
		throw BadTreeException(t, "string_cst");

	int length = TREE_STRING_LENGTH(t) - 1;
	const char* content = TREE_STRING_POINTER(t);

	_built_str =  "\"" + std::string(content, length) + "\"";
	size_t n = _built_str.find('\n');
	for (; n != std::string::npos ; n = _built_str.find('\n',n)) {
		_built_str.erase(n,1);
		_built_str.insert(n,"\\\\n ");
		n+=4;
	}
	n = _built_str.find('"');
	for (; n != std::string::npos ; n = _built_str.find('"',n)) {
		_built_str.erase(n,1);
		_built_str.insert(n,"\\\"");
		n+=2;
	}
}

std::string StringCst::print() const
{
	return _built_str;
}
