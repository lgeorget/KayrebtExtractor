/**
 * \file phi_expr.cpp
 * \author Laurent Georget
 * \date 2015-11-16
 * \brief Implementation of the PhiExpr
 */
#include <iostream>
#include <sstream>
#include <memory>
#include <cstdlib>
#include <list>
#include <gcc-plugin.h>
#include <tree.h>
#include <gimple.h>
#include "bad_gimple_exception.h"
#include "value_factory.h"
#include "expression.h"
#include "debug.h"
#include "dumper.h"
#include "phi_expr.h"

PhiExpr::PhiExpr(gimple t) : Expression(t)
{
	if (gimple_code(t) != GIMPLE_PHI)
		throw BadGimpleException(t, "gimple_phi");

	tree var = gimple_phi_result(t);
	if (var != NULL && var != NULL_TREE)
		_var = ValueFactory::INSTANCE.build(var);

	_nbArgs = gimple_phi_num_args(t);
	for (unsigned int i = 0 ; i < _nbArgs ; i++) {
		phi_arg_d* arg = gimple_phi_arg(t,i);
		if (arg)
			_args.push_back(ValueFactory::INSTANCE.build(arg->def));
	}

	if (_var) {
		std::string _varname = _var->print();
		_built_str += _varname + " = phi";
	}

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

void PhiExpr::accept(Dumper& d)
{
	d.dumpPhiExpr(this);
}
