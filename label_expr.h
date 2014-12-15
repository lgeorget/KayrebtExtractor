#ifndef LABEL_EXPR_H
#define LABEL_EXPR_H

#include <gcc-plugin.h>
#include <tree.h>
#include "expression.h"


class LabelExpr : public Expression
{
	public:
		explicit LabelExpr(tree t);
		virtual void accept(Dumper& d); // Visitor design pattern

	private:
		tree _label;

	friend std::ostream& operator<<(std::ostream& out, const LabelExpr& e);
};

#endif
