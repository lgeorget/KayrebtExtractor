#include <iostream>
#include <string>
#include <gcc-plugin.h>
#include <tree.h>
#include "value.h"
#include "value_factory.h"
#include "bad_tree_exception.h"
#include "negate_op.h"

NegateOp::NegateOp(tree t, std::string op) : Value(t), _op(op)
{
	if (TREE_CODE(t) != NEGATE_EXPR &&
	    TREE_CODE(t) != BIT_NOT_EXPR)
		throw BadTreeException(t,"one of : negate_expr, bit_not_expr");

	_val = ValueFactory::INSTANCE.build(TREE_OPERAND(t,0));
}

std::string NegateOp::print() const
{
	return _op + _val->print();
}
