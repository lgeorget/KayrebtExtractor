#ifndef ASSIGN_EXPR_H
#define ASSIGN_EXPR_H

#include <iostream>
#include <memory>
#include <gcc-plugin.h>
#include <tree.h>
#include <gimple.h>
#include "expression.h"
#include "value.h"

class AssignExpr : public Expression
{
	public:
		explicit AssignExpr(gimple t);
		virtual void accept(Dumper& d); // Visitor design pattern

	protected:
		std::shared_ptr<Value> 	_whatToSet;
		tree_code		_op;
		std::shared_ptr<Value>	_rhs1;
		std::shared_ptr<Value>	_rhs2;
		bool _anonymous;

	friend class TextDumper;
	friend class ActivityGraphDumper;
};

#endif
