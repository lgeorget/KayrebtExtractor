#include <iostream>
#include <string>
#include <gcc-plugin.h>
#include <tree.h>
#include "value.h"
#include "value_factory.h"
#include "bad_tree_exception.h"
#include "label.h"

Label::Label(tree t) : Value(t)
{
	if (TREE_CODE(t) != LABEL_DECL)
		throw BadTreeException(t,"label_decl");

	_uid = reinterpret_cast<uintptr_t>(t);
}

std::string Label::print() const
{
	return std::to_string(_uid);
}
