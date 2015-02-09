#include <iostream>
#include <cstdlib>
#include <gcc-plugin.h>
#include <gimple.h>
#include "expression.h"
#include "assign_expr.h"
#include "bad_gimple_exception.h"
#include "dumper.h"
#include "value_factory.h"

AssignExpr::AssignExpr(gimple t) : Expression(t)
{
	if (gimple_code(t) != GIMPLE_ASSIGN)
		throw BadGimpleException(t,"gimple_assign");

	_whatToSet = ValueFactory::INSTANCE.build(gimple_assign_lhs(t));
	std::string name = _whatToSet->print();
	_anonymous =  name.find('<') != std::string::npos ||
		      name.find('.') != std::string::npos;
		
	_op  = gimple_assign_rhs_code(t);
	_rhs1 = ValueFactory::INSTANCE.build(gimple_assign_rhs1(t));
	if (!gimple_assign_single_p(t)) {
		_rhs2 = ValueFactory::INSTANCE.build(gimple_assign_rhs2(t));
	}

}

void AssignExpr::accept(Dumper& d)
{
	d.dumpAssignExpr(this);
}
