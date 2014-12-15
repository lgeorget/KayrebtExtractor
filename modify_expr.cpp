#include <cstdlib>
#include <gcc-plugin.h>
#include <tree.h>
#include "expression.h"
#include "modify_expr.h"
#include "bad_tree_exception.h"
#include "dumper.h"

ModifyExpr::ModifyExpr(tree t) : Expression(t)
{
	if (TREE_CODE(t) != MODIFY_EXPR)
		throw BadTreeException(t,"modify_expr");

	tree variable = TREE_OPERAND(t,0);
	tree value = TREE_OPERAND(t,1);
}

void ModifyExpr::accept(Dumper& d)
{
	d.dumpModifyExpr(this);
}

std::ostream& operator<<(std::ostream& out, const ModifyExpr& e)
{
	out << "<var> <- <val>";
	return out;
}
