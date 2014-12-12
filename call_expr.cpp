#include <list>
#include <gcc-plugin.h>
#include <tree.h>
#include "call_expr.h"
#include "bad_tree_exception.h"

CallExpr::CallExpr(tree t) : Expression(t), _name(nullptr)
{
	if (TREE_CODE(t) != CALL_EXPR)
		throw BadTreeException(t, "call_expr");

	tree nb = TREE_OPERAND(t,0);
	_nbArgs = TREE_INT_CST_HIGH(nb) << 32
		+ TREE_INT_CST_LOW(nb)
		- 3;
	tree fn = TREE_OPERAND(t,1);
	_name = DECL_NAME(fn) ? IDENTIFIER_POINTER(DECL_NAME(fn)) : "<anonymous>";

}

std::ostream& operator<<(std::ostream& out, const CallExpr& e)
{
	out << e._name << "(... " << e._nbArgs << "arguments ...)";
	return out;
}
