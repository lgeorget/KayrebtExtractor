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
	if (TREE_CODE(t) != MEM_REF && TREE_CODE(t) != TARGET_MEM_REF)
		throw BadTreeException(t,"mem_ref");

	_ptr = ValueFactory::INSTANCE.build(TREE_OPERAND(t,0));
	_hasOffset = !integer_zerop(TREE_OPERAND(t, 1));
	if (_hasOffset)
		_offset = std::to_string(mem_ref_offset(t).to_shwi()); //safe, see <tree-flow-inline.h>

	if (TREE_CODE(t) == TARGET_MEM_REF) {
		if (TMR_INDEX(t) && TMR_INDEX(t) != NULL_TREE)
			_index = ValueFactory::INSTANCE.build(TMR_INDEX(t));
		if (TMR_INDEX2(t) && TMR_INDEX2(t) != NULL_TREE)
			_index2 = ValueFactory::INSTANCE.build(TMR_INDEX2(t));
		if (TMR_STEP(t) && TMR_STEP(t) != NULL_TREE)
			_step = ValueFactory::INSTANCE.build(TMR_STEP(t));

	}
}

std::string MemRef::print() const
{
	if (_hasOffset) {
		std::string offset = _offset + (_index ? "+ " + _index->print() : "")
			                     + (_step  ? " * " + _step->print() : "")
					     + (_index2 ? " + " + _index2->print() : "");
		return "MEM[&" + _ptr->print() + ", offset: " + offset + "B]";
	} else {
		return "*(" + _ptr->print() + ")";
	}
}
