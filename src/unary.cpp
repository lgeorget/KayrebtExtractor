#include <iostream>
#include <memory>
#include <gcc-plugin.h>
#include <tree.h>
#include "unary.h"
#include "value_factory.h"

Unary::Unary(tree t, const std::string& symbol) : Value(t), _symbol(symbol)
{
	_inside = ValueFactory::INSTANCE.build(TREE_OPERAND(t, 0));
}

std::string Unary::print() const
{
	return _symbol + _inside->print();
}

