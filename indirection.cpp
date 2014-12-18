#include <iostream>
#include <string>
#include <gcc-plugin.h>
#include <tree.h>
#include "value.h"
#include "value_factory.h"
#include "bad_tree_exception.h"
#include "indirection.h"

Indirection::Indirection(tree t, std::string&& op) : Value(t), _op(op)
{
	if (TREE_CODE(t) != INDIRECT_REF && TREE_CODE(t) != ADDR_EXPR)
		throw BadTreeException(t,"one of : indirect_ref, addr_expr");

	_val = ValueFactory::INSTANCE.build(TREE_OPERAND(t,0));
}

std::string Indirection::print() const
{
	return _op + _val->print();
}
