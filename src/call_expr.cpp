#include <iostream>
#include <sstream>
#include <memory>
#include <cstdlib>
#include <list>
#include <gcc-plugin.h>
#include <tree.h>
#include <gimple.h>
#include "call_expr.h"
#include "bad_gimple_exception.h"
#include "value_factory.h"
#include "expression.h"
#include "debug.h"
#include "dumper.h"

CallExpr::CallExpr(gimple t) : Expression(t)
{
	if (gimple_code(t) != GIMPLE_CALL)
		throw BadGimpleException(t, "gimple_call");


	tree var = gimple_call_lhs(t);
	if (var != NULL && var != NULL_TREE)
		_var = ValueFactory::INSTANCE.build(var);

	tree fn = gimple_call_fndecl(t);
	if (fn != NULL && fn != NULL_TREE)
		_name = ValueFactory::INSTANCE.build(DECL_NAME(fn));

	_nbArgs = gimple_call_num_args(t);
	for (int i = 0 ; i < _nbArgs ; i++) {
		_args.push_back(ValueFactory::INSTANCE.build(gimple_call_arg(t,i)));
	}

	if (_var)
		_built_str += _var->print() + " = ";
	if (_name)
		_built_str += _name->print();
	else
		_built_str += "<anonymous_function>";
	_built_str += "(";
	if (_nbArgs > 0) {
		_built_str += _args.front()->print();
		auto it = _args.cbegin();
		for (++it ; it != _args.cend() ; ++it) {
			_built_str += ", " + (*it)->print();
		}
	}
	_built_str += ")";
}

void CallExpr::accept(Dumper& d)
{
	d.dumpCallExpr(this);
}
