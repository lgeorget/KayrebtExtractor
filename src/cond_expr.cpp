#include <iostream>
#include <memory>
#include <cstdlib>
#include <list>
#include <gcc-plugin.h>
#include <gimple.h>
#include <gimple.h>
#include "cond_expr.h"
#include "bad_gimple_exception.h"
#include "dumper.h"
#include "value_factory.h"
#include "expr_factory.h"
#include "value.h"

CondExpr::CondExpr(gimple t) : Expression(t)
{
	if (gimple_code(t) != GIMPLE_COND)
		throw BadGimpleException(t, "cond_expr");

	_op = gimple_cond_code(t);
	_lhs = ValueFactory::INSTANCE.build(gimple_cond_lhs(t));
	_rhs = ValueFactory::INSTANCE.build(gimple_cond_rhs(t));

/*	tree a = gimple_cond_true_label(t);
	if (a != NULL && a != NULL_TREE)
		_then = ValueFactory::INSTANCE.build(gimple_cond_true_label(t));
	a = gimple_cond_false_label(t);
	if (a != NULL && a != NULL_TREE)
		_else = ValueFactory::INSTANCE.build(gimple_cond_false_label(t));
		*/
}

void CondExpr::accept(Dumper& d)
{
	d.dumpCondExpr(this);
}
