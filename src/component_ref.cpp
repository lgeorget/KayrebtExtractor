#include <iostream>
#include <string>
#include <memory>
#include <gcc-plugin.h>
#include <tree.h>
#include "component_ref.h"
#include "value.h"
#include "bad_tree_exception.h"
#include "value_factory.h"

ComponentRef::ComponentRef(tree t) : Value(t)
{
	if (TREE_CODE(t) != COMPONENT_REF)
		throw BadTreeException(t,"component_ref");

	_container = ValueFactory::INSTANCE.build(TREE_OPERAND(t,0));
	_component = ValueFactory::INSTANCE.build(TREE_OPERAND(t,1));
}

std::string ComponentRef::print() const
{
	return _container->print() + "." + _component->print();
}
