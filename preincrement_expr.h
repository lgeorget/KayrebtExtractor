#ifndef PREINCREMENT_EXPR
#define PREINCREMENT_EXPR

#include <iostream>
#include <memory>
#include <string>
#include <gcc-plugin.h>
#include <tree.h>
#include "expression.h"

class Value;

class PreincrementExpr : public Expression
{
	public:
		explicit PreincrementExpr(tree t);
		virtual void accept(Dumper& d); // Visitor design pattern

	private:
		std::shared_ptr<Value> _variable;

	friend std::ostream& operator<<(std::ostream& out, const PreincrementExpr& e);
};

#endif
