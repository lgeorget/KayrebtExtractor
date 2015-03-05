/**
 * \file constructor.cpp
 * \author Laurent Georget
 * \date 2015-03-03
 * \brief Implementation of the Constructor
 */
#include <iostream>
#include <string>
#include <memory>
#include <gcc-plugin.h>
#include <tree.h>
#include "constructor.h"
#include "value.h"
#include "bad_tree_exception.h"
#include "value_factory.h"

Constructor::Constructor(tree t) : Value(t)
{
	if (TREE_CODE(t) != CONSTRUCTOR)
		throw BadTreeException(t,"constructor");

	unsigned int i;
	tree elt;
	_built_str = "{\\n ";
	FOR_EACH_CONSTRUCTOR_VALUE(CONSTRUCTOR_ELTS(t), i, elt) {
		std::shared_ptr<Value> v = ValueFactory::INSTANCE.build(elt);
		_built_str += "\\t" + v->print() + "\\n ";
		_fields.push_back(v);
	}
	_built_str += "}";
}

std::string Constructor::print() const
{
	return _built_str;
}
