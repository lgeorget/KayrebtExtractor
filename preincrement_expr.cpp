#include <gcc-plugin.h>
#include <tree.h>
#include "bad_tree_exception.h"
#include "preincrement_expr.h"

PreincrementExpr::PreincrementExpr(tree t) : Expression(t)
{
	if (TREE_CODE(t) != PREINCREMENT_EXPR)
		throw BadTreeException(t,"preincrement_tree");
}
