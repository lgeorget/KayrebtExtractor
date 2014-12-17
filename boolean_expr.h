#ifndef BOOLEAN_EXPR_H
#define BOOLEAN_EXPR_H

#include <iostream>
#include <memory>
#include <gcc-plugin.h>
#include <tree.h>
#include "expression.h"

class Dumper;

class BooleanExpr : public Expression
{
	public:
		explicit BooleanExpr(tree t, std::string op);
		void accept(Dumper& d) override;

	private:
		const std::string _op;
		std::shared_ptr<Expression> _opl;
		std::shared_ptr<Expression> _opr;

	friend class Dumper;
};

#endif
