#ifndef COND_EXPR_H
#define COND_EXPR_H

#include <iostream>
#include <memory>
#include <gcc-plugin.h>
#include <gimple.h>
#include "expression.h"
#include "value.h"

class Dumper;

class CondExpr : public Expression
{
	public:
		explicit CondExpr(gimple t);
		void accept(Dumper& d) override;

	private:
		std::shared_ptr<Value> _lhs;
		std::shared_ptr<Value> _rhs;
		tree_code		_op;
		std::shared_ptr<Value> _then;
		std::shared_ptr<Value> _else;

	friend class ActivityGraphDumper;
};

#endif
