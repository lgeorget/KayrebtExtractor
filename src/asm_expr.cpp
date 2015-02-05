#include <iostream>
#include <string>
#include <gcc-plugin.h>
#include <gimple.h>
#include "asm_expr.h"
#include "value.h"
#include "bad_gimple_exception.h"
#include "value_factory.h"

AsmExpr::AsmExpr(gimple t) : Value(t)
{
	if (gimple_code(t) != GIMPLE_ASM)
		throw BadTreeException(t, "gimple_asm");

	_stmt = ValueFactory::INSTANCE.build(gimple_asm_string(t));
}

std::string AsmExpr::print() const
{
	return _stmt->print();
}
