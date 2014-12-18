#include <cstdlib>
#include <gcc-plugin.h>
#include <tree.h>
#include "return_expr.h"
#include "expression.h"
#include "bad_tree_exception.h"
#include "dumper.h"
#include "expr_factory.h"

ReturnExpr::ReturnExpr(tree t) : Expression(t)
{
	if (TREE_CODE(t) != RETURN_EXPR)
		throw BadTreeException(t,"RETURN_EXPR");

	//Flatten the tree, don't care about the location of the return value
	tree ret = TREE_OPERAND(t,0);
	if (ret) {
		if (TREE_CODE(ret) == MODIFY_EXPR)
			_value = ExprFactory::INSTANCE.build(TREE_OPERAND(ret,1));
		else
			_value = ExprFactory::INSTANCE.build(ret);
	}
}

void ReturnExpr::accept(Dumper& d)
{
	d.dumpReturnExpr(this);
}
