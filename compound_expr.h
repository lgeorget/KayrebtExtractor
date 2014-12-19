#ifndef COMPOUND_EXPR_H
#define COMPOUND_EXPR_H

#include <iostream>
#include <memory>
#include <gcc-plugin.h>
#include <tree.h>
#include "expression.h"

class CompoundExpr : public Expression
{
	public:
		explicit CompoundExpr(tree t);
		virtual void accept(Dumper& d); // Visitor design pattern

	private:
		std::shared_ptr<Expression> _first;
		std::shared_ptr<Expression> _second;

	friend class TextDumper;
};

#endif

