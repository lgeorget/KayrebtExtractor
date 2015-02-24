#include <cstdlib>
#include <gcc-plugin.h>
#include <gimple.h>
#include "bad_gimple_exception.h"
#include "goto_expr.h"
#include "dumper.h"
#include "value.h"
#include "value_factory.h"

GotoExpr::GotoExpr(gimple t) : Expression(t)
{
	if (gimple_code(t) != GIMPLE_GOTO)
		throw BadGimpleException(t,"goto");

//	_label = ValueFactory::INSTANCE.build(gimple_goto_dest(t));
}

void GotoExpr::accept(Dumper& d)
{
	d.dumpGotoExpr(this);
}
