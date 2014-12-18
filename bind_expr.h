#ifndef BIND_EXPR_H
#define BIND_EXPR_H

#include <iostream>
#include <memory>
#include <gcc-plugin.h>
#include <tree.h>
#include "expression.h"
#include "value.h"

class BindExpr : public Expression
{
	public:
		explicit BindExpr(tree t);
		virtual void accept(Dumper& d); // Visitor design pattern

	private:
		std::shared_ptr<Expression> _vars;
		std::shared_ptr<Expression> _body;

	friend class TextDumper;
};

#endif

