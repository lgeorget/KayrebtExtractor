#include <iostream>
#include <memory>
#include <cstdlib>
#include <list>
#include <gcc-plugin.h>
#include <tree.h>
#include "call_expr.h"
#include "bad_tree_exception.h"
#include "dumper.h"
#include "expr_factory.h"
#include "value_factory.h"
#include "value.h"
#include "debug.h"

CallExpr::CallExpr(tree t) : Expression(t), _name(nullptr), _nbArgs(0)
{
	assert_tree(t);
	if (TREE_CODE(t) != CALL_EXPR)
		throw BadTreeException(t, "call_expr");

	tree nb = TREE_OPERAND(t,0);
	assert_tree(nb);
	_nbArgs = (TREE_INT_CST_HIGH(nb) << 32)
		+ TREE_INT_CST_LOW(nb)
		- 3;
	assert_tree(TREE_OPERAND(t,1));
	tree fn = TREE_OPERAND(t,1);
	assert_tree(fn);
	_name = ValueFactory::INSTANCE.build(fn);
	for (int i = 0 ; i < _nbArgs ; i++) {
		assert_tree(TREE_OPERAND(t,i+3));
		_args.push_back(ExprFactory::INSTANCE.build(TREE_OPERAND(t,i+3)));
	}
}

void CallExpr::accept(Dumper& d)
{
	d.dumpCallExpr(this);
}
