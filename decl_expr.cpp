#include <cstdlib>
#include <gcc-plugin.h>
#include <tree.h>
#include "decl_expr.h"
#include "expression.h"
#include "bad_tree_exception.h"
#include "dumper.h"
#include "value_factory.h"

DeclExpr::DeclExpr(tree t) : Expression(t)
{
	if (TREE_CODE(t) != DECL_EXPR)
		throw BadTreeException(t,"decl_expr");

	_name = ValueFactory::INSTANCE.build(DECL_EXPR_DECL(t));
}

void DeclExpr::accept(Dumper& d)
{
	d.dumpDeclExpr(this);
}

std::ostream& operator<<(std::ostream& out, const DeclExpr& e)
{
	out << e._name.get();
	return out;
}
