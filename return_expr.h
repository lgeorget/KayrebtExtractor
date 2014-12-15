#ifndef RETURN_EXPR_H
#define RETURN_EXPR_H

#include <gcc-plugin.h>
#include <tree.h>
#include "expression.h"

class ReturnExpr : public Expression
{
	public:
		explicit ReturnExpr(tree t);
		virtual void accept(Dumper& d); // Visitor design pattern

	private:
		tree _value;

	friend std::ostream& operator<<(std::ostream& out, const ReturnExpr& e);
};

#endif
