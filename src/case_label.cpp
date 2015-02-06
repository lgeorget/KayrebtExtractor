#include <iostream>
#include <cstdlib>
#include <gcc-plugin.h>
#include <tree.h>
#include "bad_tree_exception.h"
#include "case_label.h"
#include "dumper.h"
#include "value_factory.h"

CaseLabel::CaseLabel(tree t) : Value(t)
{
	if (TREE_CODE(t) != CASE_LABEL_EXPR)
		throw BadTreeException(t,"case_label_expr");

	if (TREE_OPERAND(t,0))
		_lowValue = ValueFactory::INSTANCE.build(TREE_OPERAND(t,0));
	if (TREE_OPERAND(t,1))
		_highValue = ValueFactory::INSTANCE.build(TREE_OPERAND(t,1));
	_label = ValueFactory::INSTANCE.build(TREE_OPERAND(t,2));

	if (_lowValue) {
		_built_str += _lowValue->print();
		if (_highValue) {
			_built_str +=  " ... " + _highValue->print();
		}
	}
	else
		_built_str += "default";
	_built_str += _label->print();
}

std::string CaseLabel::print() const
{
	return _built_str;
}
