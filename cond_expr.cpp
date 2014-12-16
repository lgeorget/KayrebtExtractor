#include <iostream>
#include <memory>
#include <cstdlib>
#include <list>
#include <gcc-plugin.h>
#include <tree.h>
#include "call_expr.h"
#include "bad_tree_exception.h"
#include "dumper.h"
#include "value_factory.h"
#include "expr_factory.h"
#include "value.h"

CondExpr::CondExpr(tree t) : Expression(t)
{
	if (TREE_CODE(t) != COND_EXPR)
		throw BadTreeException(t, "cond_expr");

	_cond = ExprFactory::INSTANCE.build(TREE_OPERAND(t,0));
	_then = ExprFactory::INSTANCE.build(TREE_OPERAND(t,1));
	if (TREE_OPERAND(t,2))
		_else = ExprFactory::INSTANCE.build(TREE_OPERAND(t,2));
	else
		_else = std::shared_ptr<Expression>();
}

void CondExpr::accept(Dumper& d)
{
	d.dumpCondExpr(this);
}

std::ostream& operator<<(std::ostream& out, const CondExpr& e)
{
	out << "if " << *e._cond 
	    << " then : "
	    << *e._then;
	if (e._else)
	    out << " else : "
	        << *e._else;

	out << std::endl;
	return out;
}
