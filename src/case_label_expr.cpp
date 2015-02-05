#include <iostream>
#include <cstdlib>
#include <gcc-plugin.h>
#include <tree.h>
#include <gimple.h>
#include "bad_gimple_exception.h"
#include "case_label_expr.h"
#include "dumper.h"
#include "value_factory.h"

CaseLabelExpr::CaseLabelExpr(gimple t) : Expression(t)
{
	if (TREE_CODE(t) != CASE_LABEL_EXPR)
		throw BadTreeException(t,"case_label_expr");

	if (TREE_OPERAND(t,0))
		_lowValue = ValueFactory::INSTANCE.build(TREE_OPERAND(t,0));
	if (TREE_OPERAND(t,1))
		_highValue = ValueFactory::INSTANCE.build(TREE_OPERAND(t,1));
	_label = ValueFactory::INSTANCE.build(TREE_OPERAND(t,2));
}

void CaseLabelExpr::accept(Dumper& d)
{
	d.dumpCaseLabelExpr(this);
}
