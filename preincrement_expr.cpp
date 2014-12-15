#include <cstdlib>
#include <gcc-plugin.h>
#include <tree.h>
#include "bad_tree_exception.h"
#include "dumper.h"
#include "preincrement_expr.h"

PreincrementExpr::PreincrementExpr(tree t) : Expression(t)
{
	if (TREE_CODE(t) != PREDECREMENT_EXPR)
		throw BadTreeException(t,"preincrement_tree");
}

void PreincrementExpr::accept(Dumper& d)
{
	d.dumpPreincrementExpr(this);
}

std::ostream& operator<<(std::ostream& out, const PreincrementExpr& e)
{
	out << "--<var>";
	return out;
}
