#ifndef LABEL_EXPR_H
#define LABEL_EXPR_H

#include <gcc-plugin.h>
#include <tree.h>
#include "expression.h"


class LabelExpr : public Expression
{
	public:
		explicit LabelExpr(tree t);

	private:
		tree _label;
};

#endif
