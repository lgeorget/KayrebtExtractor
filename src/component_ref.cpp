/**
 * \file component_ref.cpp
 * \author Laurent Georget
 * \date 2015-03-03
 * \brief Implementation of the ComponentRef
 */
#include <iostream>
#include <string>
#include <memory>
#include <gcc-plugin.h>
#include <tree.h>
#include "component_ref.h"
#include "value.h"
#include "bad_tree_exception.h"
#include "value_factory.h"

ComponentRef::ComponentRef(tree t, const std::string& symbol) : Value(t), _symbol(symbol)
{
	if (TREE_CODE(t) != COMPONENT_REF)
		throw BadTreeException(t,"component_ref");

	_container = ValueFactory::INSTANCE.build(TREE_OPERAND(t,0));
	_component = ValueFactory::INSTANCE.build(TREE_OPERAND(t,1));
}

std::string ComponentRef::print() const
{
	return _container->print() + _symbol + _component->print();
}
