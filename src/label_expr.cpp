/**
 * \file label_expr.cpp
 * \author Laurent Georget
 * \date 2015-03-03
 * \brief Implementation of the LabelExpr
 */
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
		throw BadGimpleException(t,"gimple_label");

	_label = ValueFactory::INSTANCE.build(gimple_label_label(t));
}

void LabelExpr::accept(Dumper& d)
{
	d.dumpLabelExpr(this);
}
