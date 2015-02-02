#include <iostream>
#include <string>
#include <gcc-plugin.h>
#include <tree.h>
#include "asm_expr.h"
#include "value.h"
#include "bad_tree_exception.h"
#include "value_factory.h"

AsmExpr::AsmExpr(tree t) : Value(t)
{
	if (TREE_CODE(t) != ASM_EXPR)
		throw BadTreeException(t, "asm_expr");

	_stmt = ValueFactory::INSTANCE.build(ASM_STRING(t));
}

std::string AsmExpr::print() const
{
	return _stmt->print();
}
