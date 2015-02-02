#include <iostream>
#include <memory>
#include <cstdlib>
#include <gcc-plugin.h>
#include <tree.h>
#include "compound_expr.h"
#include "bad_tree_exception.h"
#include "dumper.h"
#include "expr_factory.h"

CompoundExpr::CompoundExpr(tree t) : Expression(t)
{
	if (TREE_CODE(t) != COMPOUND_EXPR)
		throw BadTreeException(t, "compound_expr");

	_first = ExprFactory::INSTANCE.build(TREE_OPERAND(t,0));
	_second = ExprFactory::INSTANCE.build(TREE_OPERAND(t,1));
}

void CompoundExpr::accept(Dumper& d)
{
	d.dumpCompoundExpr(this);
}
