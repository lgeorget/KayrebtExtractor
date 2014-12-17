#include <iostream>
#include <memory>
#include <gcc-plugin.h>
#include <tree.h>
#include "expression.h"
#include "expr_factory.h"
#include "dumper.h"
#include "bad_tree_exception.h"

BooleanExpr::BooleanExpr(tree t, std::string op) : Expression(t), _op(op)
{
	if (TREE_CODE(t) < TRUTH_ANDIF_EXPR &&
	    TREE_CODE(t) > TRUTH_XOR_EXPR)
		throw BadTreeException(t,
			"one of : TRUTH_ANDIF_EXPR, "
				 "TRUTH_ORIF_EXPR, "
				 "TRUTH_AND_EXPR, "
				 "TRUTH_OR_EXPR, "
				 "TRUTH_XOR_EXPR");

	_opl = ExprFactory::INSTANCE.build(TREE_OPERAND(t,0));
	_opr = ExprFactory::INSTANCE.build(TREE_OPERAND(t,1));
}

void BooleanExpr::accept(Dumper& d)
{
	d.dumpBooleanExpr(this);
}
