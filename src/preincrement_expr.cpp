#include <cstdlib>
#include <gcc-plugin.h>
#include <tree.h>
#include "bad_tree_exception.h"
#include "dumper.h"
#include "preincrement_expr.h"
#include "value_factory.h"
#include "value.h"

PreincrementExpr::PreincrementExpr(tree t) : Expression(t)
{
	if (TREE_CODE(t) != PREINCREMENT_EXPR)
		throw BadTreeException(t,"preincrement_tree");

	_variable = ValueFactory::INSTANCE.build(TREE_OPERAND(t,0));
}

void PreincrementExpr::accept(Dumper& d)
{
	d.dumpPreincrementExpr(this);
}

std::ostream& operator<<(std::ostream& out, const PreincrementExpr& e)
{
	out << "++" << e._variable.get();
	return out;
}
