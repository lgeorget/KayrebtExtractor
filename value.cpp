#include <iostream>
#include <string>
#include <gcc-plugin.h>
#include <tree.h>
#include "value.h"

Value::Value(tree t) : _inner(t)
{}

std::string Value::print() const
{
	return std::string("Uninitialized value : ") + tree_code_name[TREE_CODE(_inner)];
}

std::ostream& operator<<(std::ostream& out, const Value* v)
{
	out << v->print();
	return out;
}
