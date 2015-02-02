#ifndef PREINCREMENT_EXPR_H
#define PREINCREMENT_EXPR_H

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
	friend class TextDumper;	friend class ActivityGraphDumper;
};

#endif
