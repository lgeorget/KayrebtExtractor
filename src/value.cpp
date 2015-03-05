/**
 * \file value.cpp
 * \author Laurent Georget
 * \date 2015-03-03
 * \brief Implementation of the abstract class Value
 */
#include <iostream>
#include <string>
#include <gcc-plugin.h>
#include <tree.h>
#include "value.h"
#include "label.h"

Value::Value(tree t) : _inner(t), _uid(reinterpret_cast<uintptr_t>(t))
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

bool Value::operator<(const Value& other) const
{
	return _uid < other._uid;
}

uintptr_t Value::getUid() const
{
	return _uid;
}
