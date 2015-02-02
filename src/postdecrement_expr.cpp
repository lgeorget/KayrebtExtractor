#include <cstdlib>
#include <gcc-plugin.h>
#include <tree.h>
#include "bad_tree_exception.h"
#include "dumper.h"
#include "postdecrement_expr.h"
#include "value_factory.h"
#include "value.h"

PostdecrementExpr::PostdecrementExpr(tree t) : Expression(t)
{
	if (TREE_CODE(t) != POSTDECREMENT_EXPR)
		throw BadTreeException(t,"postdecrement_tree");

	_variable = ValueFactory::INSTANCE.build(TREE_OPERAND(t,0));
}

void PostdecrementExpr::accept(Dumper& d)
{
	d.dumpPostdecrementExpr(this);
}

std::ostream& operator<<(std::ostream& out, const PostdecrementExpr& e)
{
	out << e._variable.get() << "--";
	return out;
}
