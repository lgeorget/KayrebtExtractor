#include <iostream>
#include <sstream>
#include <string>
#include <memory>
#include <gcc-plugin.h>
#include <tree.h>
#include "ternary_op.h"
#include "value.h"
#include "bad_tree_exception.h"
#include "expr_factory.h"
#include "value_factory.h"
#include "dumper.h"

TernaryOp::TernaryOp(tree t) : Value(t)
{
	if (TREE_CODE(t) != COND_EXPR)
		throw BadTreeException(t,"cond_expr");

	_cond = ExprFactory::INSTANCE.build(TREE_OPERAND(t,0));
	_yes = ValueFactory::INSTANCE.build(TREE_OPERAND(t,1));
	_no = ValueFactory::INSTANCE.build(TREE_OPERAND(t,2));
}

std::string TernaryOp::print() const
{
	std::ostringstream out;
	Dumper d(&out, false);
	_cond->accept(d);
	out << " ? " << _yes->print() << " : " << _no->print();
	return out.str();
}

