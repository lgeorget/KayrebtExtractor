#include <gcc-plugin.h>
#include <tree.h>
#include "bad_tree_exception.h"
#include "goto_expr.h"

GotoExpr::GotoExpr(tree t) : Expression(t)
{
	if (TREE_CODE(t) != GOTO_EXPR)
		throw BadTreeException(t,"label_tree");

	_label = TREE_OPERAND(t, 0);
}
