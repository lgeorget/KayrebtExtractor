#include <gcc-plugin.h>
#include <tree.h>
#include "bad_tree_exception.h"
#include "label_expr.h"

LabelExpr::LabelExpr(tree t) : Expression(t)
{
	if (TREE_CODE(t) != LABEL_EXPR)
		throw BadTreeException(t,"label_tree");

	_label = TREE_OPERAND(t, 0);
}
