#include <iostream>
#include <cstdlib>
#include <gcc-plugin.h>
#include <gimple.h>
#include "bad_gimple_exception.h"
#include "label_expr.h"
#include "dumper.h"
#include "value_factory.h"

LabelExpr::LabelExpr(gimple t) : Expression(t)
{
	if (gimple_code(t) != GIMPLE_LABEL)
		throw BadTreeException(t,"gimple_label");

	_label = ValueFactory::INSTANCE.build(gimple_label_label(t));
}

void LabelExpr::accept(Dumper& d)
{
	d.dumpLabelExpr(this);
}
