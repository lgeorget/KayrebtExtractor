/**
 * \file expression.cpp
 * \author Laurent Georget
 * \date 2015-03-03
 * \brief Implementation of the virtual Expression
 */
#include <iostream>
#include <memory>
#include <cstdlib>
#include <gcc-plugin.h>
#include <gimple.h>
#include "expression.h"
#include "dumper.h"

Expression::Expression(gimple t) : _expr(t)
{}

void Expression::accept(Dumper& d)
{
	d.dumpExpression(this);
}

std::ostream& operator<<(std::ostream& out, const Expression& e)
{
	out << "Unknown expression : " << gimple_code_name[gimple_code(e._expr)];
	return out;
}
