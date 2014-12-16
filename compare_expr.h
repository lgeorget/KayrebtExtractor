#ifndef COMPARE_EXPR_H
#define COMPARE_EXPR_H

#include <iostream>
#include <memory>
#include <gcc-plugin.h>
#include <tree.h>
#include "expression.h"
#include "value.h"

class Dumper;

class CompareExpr : public Expression
{
	public:
		explicit CompareExpr(tree t, std::string op);
		void accept(Dumper& d) override;

	private:
		const std::string _op;
		std::shared_ptr<Value> _opl;
		std::shared_ptr<Value> _opr;

	friend class Dumper;
};

#endif
