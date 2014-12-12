#ifndef RETURN_EXPR_H
#define RETURN_EXPR_H

#include <gcc-plugin.h>
#include <tree.h>
#include "expression.h"

class ReturnExpr : public Expression
{
	public:
		explicit ReturnExpr(tree t);

	private:
		tree _value;
};

#endif
