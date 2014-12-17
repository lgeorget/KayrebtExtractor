#include <iostream>
#include <string>
#include <gcc-plugin.h>
#include <tree.h>
#include "value.h"
#include "value_factory.h"
#include "bad_tree_exception.h"
#include "negate_op.h"

NegateOp::NegateOp(tree t) : Value(t)
{
	if (TREE_CODE(t) != NEGATE_EXPR)
		throw BadTreeException(t,"negate_expr");

	_op = ValueFactory::INSTANCE.build(TREE_OPERAND(t,0));
}

std::string NegateOp::print() const
{
	return "-" + _op->print();
}
