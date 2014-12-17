#include <iostream>
#include <memory>
#include <cstdlib>
#include <list>
#include <gcc-plugin.h>
#include <tree.h>
#include "switch_expr.h"
#include "bad_tree_exception.h"
#include "dumper.h"
#include "value_factory.h"
#include "expr_factory.h"

SwitchExpr::SwitchExpr(tree t) : Expression(t)
{
	if (TREE_CODE(t) != SWITCH_EXPR)
		throw BadTreeException(t, "switch_expr");

	_cond = ExprFactory::INSTANCE.build(TREE_OPERAND(t,0));
	_body = ExprFactory::INSTANCE.build(TREE_OPERAND(t,1));
}

void SwitchExpr::accept(Dumper& d)
{
	d.dumpSwitchExpr(this);
}
