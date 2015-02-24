#include <iostream>
#include <string>
#include <gcc-plugin.h>
#include <gimple.h>
#include "asm_expr.h"
#include "value.h"
#include "bad_gimple_exception.h"
#include "value_factory.h"
#include "dumper.h"

AsmExpr::AsmExpr(gimple t) : Expression(t)
{
	if (gimple_code(t) != GIMPLE_ASM)
		throw BadGimpleException(t, "gimple_asm");

	_stmt = gimple_asm_string(t);
}

void AsmExpr::accept(Dumper& d)
{
	d.dumpAsmExpr(this);
}
