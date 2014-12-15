#ifndef GOTO_EXPR_H
#define GOTO_EXPR_H

#include <gcc-plugin.h>
#include <tree.h>
#include "expression.h"


class GotoExpr : public Expression
{
	public:
		explicit GotoExpr(tree t);
		virtual void accept(Dumper& d); // Visitor design pattern

	private:
		tree _label;

	friend std::ostream& operator<<(std::ostream& out, const GotoExpr& e);
};

#endif
