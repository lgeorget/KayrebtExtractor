#include <iostream>
#include <cstdlib>
#include <gcc-plugin.h>
#include <tree.h>
#include "bad_tree_exception.h"
#include "case_label_expr.h"
#include "dumper.h"
#include "value_factory.h"

CaseLabelExpr::CaseLabelExpr(tree t) : Expression(t)
{
	if (TREE_CODE(t) != CASE_LABEL_EXPR)
		throw BadTreeException(t,"case_label_tree");

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
