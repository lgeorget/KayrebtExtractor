#include <iostream>
#include <sstream>
#include <memory>
#include <cstdlib>
#include <list>
#include <gcc-plugin.h>
#include <tree.h>
#include "call_expr.h"
#include "bad_tree_exception.h"
#include "value_factory.h"
#include "value.h"
#include "debug.h"
#include "text_dumper.h"

CallExpr::CallExpr(tree t) : Value(t), _name(nullptr), _nbArgs(0)
{
	assert_tree(t);
	if (TREE_CODE(t) != CALL_EXPR)
		throw BadTreeException(t, "call_expr");

	tree nb = TREE_OPERAND(t,0);
	assert_tree(nb);
	_nbArgs = (TREE_INT_CST_HIGH(nb) << 32)
		+ TREE_INT_CST_LOW(nb)
		- 3;
	assert_tree(TREE_OPERAND(t,1));
	tree fn = TREE_OPERAND(t,1);
	assert_tree(fn);
	_name = ValueFactory::INSTANCE.build(fn);
	for (int i = 0 ; i < _nbArgs ; i++) {
		assert_tree(TREE_OPERAND(t,i+3));
		_args.push_back(ValueFactory::INSTANCE.build(TREE_OPERAND(t,i+3)));
	}

	std::stringstream out;
	out << _name->print() << "_" << _nbArgs << "_(";
	if (_nbArgs > 0) {
		out << _args.front()->print();
		auto it = _args.cbegin();
		for (++it ; it != _args.cend() ; ++it) {
			out << ", " << (*it)->print();
		}
	}
	out << ")";
	_built_str = out.str();
}

std::string CallExpr::print() const
{
	return _built_str;
}
