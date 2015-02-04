#ifndef RETURN_EXPR_H
#define RETURN_EXPR_H

#include <iostream>
#include <memory>
#include <gcc-plugin.h>
#include <tree.h>
#include "expression.h"
#include "value.h"

class ReturnExpr : public Expression
{
	public:
		explicit ReturnExpr(tree t);
		virtual void accept(Dumper& d); // Visitor design pattern

	private:
		std::shared_ptr<Expression> _value;

	friend class TextDumper;	friend class ActivityGraphDumper;
};

#endif