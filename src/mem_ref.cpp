/**
 * \file mem_ref.cpp
 * \author Laurent Georget
 * \date 2015-03-03
 * \brief Implementation of the MemRef
 */
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
	_hasOffset = !integer_zerop(TREE_OPERAND(t, 1));
	if (_hasOffset)
		_offset = std::to_string(mem_ref_offset(t).to_shwi()); //safe, see <tree-inline.h>
}

std::string MemRef::print() const
{
	if (_hasOffset)
		return "MEM[&" + _ptr->print() + ", offset: " + _offset + "B]";
	else
		return "*(" + _ptr->print() + ")";
}
