#include <cstdlib>
#include <gcc-plugin.h>
#include <tree.h>
#include "bad_tree_exception.h"
#include "dumper.h"
#include "postincrement_expr.h"
#include "value_factory.h"
#include "value.h"

PostincrementExpr::PostincrementExpr(tree t) : Expression(t)
{
	if (TREE_CODE(t) != POSTINCREMENT_EXPR)
		throw BadTreeException(t,"postincrement_tree");

	_variable = ValueFactory::INSTANCE.build(TREE_OPERAND(t,0));
}

void PostincrementExpr::accept(Dumper& d)
{
	d.dumpPostincrementExpr(this);
}

std::ostream& operator<<(std::ostream& out, const PostincrementExpr& e)
{
	out << e._variable.get() << "++";
	return out;
}
