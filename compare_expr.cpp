#include <iostream>
#include <memory>
#include <gcc-plugin.h>
#include <tree.h>
#include "expression.h"
#include "value.h"
#include "value_factory.h"
#include "dumper.h"
#include "bad_tree_exception.h"

CompareExpr::CompareExpr(tree t, std::string op) : Expression(t), _op(op)
{
	if (TREE_CODE(t) < LT_EXPR &&
	    TREE_CODE(t) > NE_EXPR)
		throw BadTreeException(t,"one of : LT_TREE, LE_TREE, GT_TREE, GE_TREE, EQ_TREE, or NE_TREE");

	_opl = ValueFactory::INSTANCE.build(TREE_OPERAND(t,0));
	_opr = ValueFactory::INSTANCE.build(TREE_OPERAND(t,1));
}

void CompareExpr::accept(Dumper& d)
{
	d.dumpCompareExpr(this);
}

