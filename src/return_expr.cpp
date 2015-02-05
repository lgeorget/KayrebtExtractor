#include <cstdlib>
#include <gcc-plugin.h>
#include <gimple.h>
#include "return_expr.h"
#include "expression.h"
#include "bad_gimple_exception.h"
#include "dumper.h"
#include "value_factory.h"

ReturnExpr::ReturnExpr(gimple t) : Expression(t)
{
	if (gimple_code(t) != GIMPLE_RETURN)
		throw BadGimpleException(t,"gimple_return");

	tree val = gimple_return_retval(t);
	if (val != NULL && val != NULL_TREE)
		_value = ValueFactory::INSTANCE.build(val);
}

void ReturnExpr::accept(Dumper& d)
{
	d.dumpReturnExpr(this);
}
