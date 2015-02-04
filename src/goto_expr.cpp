#include <cstdlib>
#include <gcc-plugin.h>
#include <tree.h>
#include "bad_tree_exception.h"
#include "goto_expr.h"
#include "dumper.h"
#include "value.h"
#include "value_factory.h"

GotoExpr::GotoExpr(tree t) : Expression(t)
{
	if (TREE_CODE(t) != GOTO_EXPR)
		throw BadTreeException(t,"label_tree");

	_label = ValueFactory::INSTANCE.build(TREE_OPERAND(t, 0));
}

void GotoExpr::accept(Dumper& d)
{
	d.dumpGotoExpr(this);
}

std::ostream& operator<<(std::ostream& out, const GotoExpr& e)
{
	out << "goto " << e._label->print();
	return out;
}