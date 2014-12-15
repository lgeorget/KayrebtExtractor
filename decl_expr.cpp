#include <cstdlib>
#include <gcc-plugin.h>
#include <tree.h>
#include "decl_expr.h"
#include "expression.h"
#include "bad_tree_exception.h"
#include "dumper.h"

DeclExpr::DeclExpr(tree t) : Expression(t)
{
	if (TREE_CODE(t) != DECL_EXPR)
		throw BadTreeException(t,"decl_expr");

	tree id = DECL_NAME(t);
	const char* name = nullptr;
	//if (id)
		//name = IDENTIFIER_POINTER(id);
	//if (!name)
		name = "<unnamed>";
	_name = std::string(name);
}

void DeclExpr::accept(Dumper& d)
{
	d.dumpDeclExpr(this);
}

std::ostream& operator<<(std::ostream& out, const DeclExpr& e)
{
//	out << e._name;
	return out;
}
