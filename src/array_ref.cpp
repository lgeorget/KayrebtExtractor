/**
 * \file array_ref.cpp
 * \author Laurent Georget
 * \date 2015-03-03
 * \brief Implementation of the ArrayRef
 */
#include <iostream>
#include <string>
#include <memory>
#include <gcc-plugin.h>
#include <tree.h>
#include "array_ref.h"
#include "value.h"
#include "bad_tree_exception.h"
#include "value_factory.h"

ArrayRef::ArrayRef(tree t) : Value(t)
{
	if (TREE_CODE(t) != ARRAY_REF)
		throw BadTreeException(t,"array_ref");

	_array = ValueFactory::INSTANCE.build(TREE_OPERAND(t,0));
	_index = ValueFactory::INSTANCE.build(TREE_OPERAND(t,1));
}

std::string ArrayRef::print() const
{
	return _array->print() + "[" + _index->print() + "]";
}
