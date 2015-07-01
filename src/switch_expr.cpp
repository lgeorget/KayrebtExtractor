/**
 * \file switch_expr.cpp
 * \author Laurent Georget
 * \date 2015-03-03
 * \brief Implementation of the SwitchExpr
 */
#include <iostream>
#include <memory>
#include <cstdlib>
#include <list>
#include <gcc-plugin.h>
#include <gimple.h>
#include "switch_expr.h"
#include "bad_gimple_exception.h"
#include "dumper.h"
#include "value_factory.h"

SwitchExpr::SwitchExpr(gimple t) : Expression(t)
{
	if (gimple_code(t) != GIMPLE_SWITCH)
		throw BadGimpleException(t, "gimple_switch");

	_var = ValueFactory::INSTANCE.build(gimple_switch_index(t));
	unsigned int nbLabs = gimple_switch_num_labels(t);
	for (unsigned int i = 0 ; i < nbLabs ; i++)
		_labels.push_back(ValueFactory::INSTANCE.build(gimple_switch_label(t,i)));
}

void SwitchExpr::accept(Dumper& d)
{
	d.dumpSwitchExpr(this);
}
