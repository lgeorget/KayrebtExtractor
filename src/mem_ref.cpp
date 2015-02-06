#include <iostream>
#include <string>
#include <memory>
#include <gcc-plugin.h>
#include <tree.h>
#include "mem_ref.h"
#include "value.h"
#include "bad_tree_exception.h"
#include "value_factory.h"

MemRef::MemRef(tree t) : Value(t)
{
	if (TREE_CODE(t) != MEM_REF)
		throw BadTreeException(t,"mem_ref");

	_ptr = ValueFactory::INSTANCE.build(TREE_OPERAND(t,0));
}

std::string MemRef::print() const
{
	return "*(" + _ptr->print() + ")";
}
