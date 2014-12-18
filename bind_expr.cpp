#include <iostream>
#include <memory>
#include <cstdlib>
#include <gcc-plugin.h>
#include <tree.h>
#include "bind_expr.h"
#include "bad_tree_exception.h"
#include "dumper.h"
#include "expr_factory.h"

BindExpr::BindExpr(tree t) : Expression(t)
{
	if (TREE_CODE(t) != BIND_EXPR)
		throw BadTreeException(t, "bind_expr");

	_vars = ExprFactory::INSTANCE.build(BIND_EXPR_VARS(t));
	_body = ExprFactory::INSTANCE.build(BIND_EXPR_BODY(t));
}

void BindExpr::accept(Dumper& d)
{
	d.dumpBindExpr(this);
}
