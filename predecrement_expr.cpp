#include <cstdlib>
#include <gcc-plugin.h>
#include <tree.h>
#include "bad_tree_exception.h"
#include "dumper.h"
#include "predecrement_expr.h"
#include "value_factory.h"
#include "value.h"

PredecrementExpr::PredecrementExpr(tree t) : Expression(t)
{
	if (TREE_CODE(t) != PREDECREMENT_EXPR)
		throw BadTreeException(t,"predecrement_tree");

	_variable = ValueFactory::INSTANCE.build(TREE_OPERAND(t,0));
}

void PredecrementExpr::accept(Dumper& d)
{
	d.dumpPredecrementExpr(this);
}

std::ostream& operator<<(std::ostream& out, const PredecrementExpr& e)
{
	out << "--" << e._variable.get();
	return out;
}
