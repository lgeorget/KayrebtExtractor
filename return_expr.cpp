#include <gcc-plugin.h>
#include <tree.h>
#include "return_expr.h"
#include "expression.h"
#include "bad_tree_exception.h"

ReturnExpr::ReturnExpr(tree t) : Expression(t)
{
	if (TREE_CODE(t) != RETURN_EXPR)
		throw BadTreeException(t,"RETURN_EXPR");

	_value = TREE_OPERAND(t,0);
}


