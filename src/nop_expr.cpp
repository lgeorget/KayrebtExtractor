/**
 * \file nop_expr.cpp
 * \author Laurent Georget
 * \date 2015-03-03
 * \brief Implementation of the NopExpr
 */
#include <iostream>
#include <memory>
#include <gcc-plugin.h>
#include <gimple.h>
#include "nop_expr.h"
#include "bad_gimple_exception.h"
#include "dumper.h"

NopExpr::NopExpr(gimple t) : Expression(t)
{}

void NopExpr::accept(Dumper& d)
{
	d.dumpNopExpr(this);
}
