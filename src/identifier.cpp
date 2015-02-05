#include <iostream>
#include <gcc-plugin.h>
#include <tree.h>
#include "value.h"
#include "identifier.h"
#include "bad_gimple_exception.h"

Identifier::Identifier(tree t) : Value(t)
{
	if (t && TREE_CODE(t) != IDENTIFIER_NODE)
		throw BadTreeException(t,"decl_name");

	if (t && t != NULL_TREE)
		_name = IDENTIFIER_POINTER(t);
	else
		_name = "<anonymous>";
}

std::string Identifier::print() const
{
	return _name;
}

