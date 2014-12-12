#include <cstdlib>
#include <gcc-plugin.h>
#include <tree.h>
#include "decl_expr.h"
#include "expression.h"
#include "bad_tree_exception.h"

DeclExpr::DeclExpr(tree t) : Expression(t)
{
	if (TREE_CODE(t) != DECL_EXPR)
		throw BadTreeException(t,"decl_expr");

	tree id = DECL_NAME(t);
	_name = id ? IDENTIFIER_POINTER(id) : "<unnamed>";
}

