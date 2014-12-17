#include <iostream>
#include <cstdlib>
#include <gcc-plugin.h>
#include <tree.h>
#include "bad_tree_exception.h"
#include "label_expr.h"
#include "dumper.h"
#include "value_factory.h"

LabelExpr::LabelExpr(tree t) : Expression(t)
{
	if (TREE_CODE(t) != LABEL_EXPR)
		throw BadTreeException(t,"label_tree");

	_label = ValueFactory::INSTANCE.build(TREE_OPERAND(t, 0));
}

void LabelExpr::accept(Dumper& d)
{
	d.dumpLabelExpr(this);
}

std::ostream& operator<<(std::ostream& out, const LabelExpr& e)
{
	out << e._label->print();
	return out;
}
