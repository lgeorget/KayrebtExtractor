#include <iostream>
#include <memory>
#include <cstdlib>
#include <gcc-plugin.h>
#include <tree.h>
#include "expression.h"
#include "dumper.h"

Expression::Expression(tree t) : _expr(t)
{}

void Expression::accept(Dumper& d)
{
	d.dumpExpression(this);
}

std::ostream& operator<<(std::ostream& out, const Expression& e)
{
	out << TREE_CODE(e._expr) << " " << tree_code_name[TREE_CODE(e._expr)];
	return out;
}
