#ifndef GOTO_EXPR_H
#define GOTO_EXPR_H

#include <gcc-plugin.h>
#include <tree.h>
#include "expression.h"


class GotoExpr : public Expression
{
	public:
		explicit GotoExpr(tree t);

	private:
		tree _label;
};

#endif
