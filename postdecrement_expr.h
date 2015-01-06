#ifndef POSTDECREMENT_EXPR_H
#define POSTDECREMENT_EXPR_H

#include <iostream>
#include <memory>
#include <string>
#include <gcc-plugin.h>
#include <tree.h>
#include "expression.h"

class Value;

class PostdecrementExpr : public Expression
{
	public:
		explicit PostdecrementExpr(tree t);
		virtual void accept(Dumper& d); // Visitor design pattern

	private:
		std::shared_ptr<Value> _variable;

	friend std::ostream& operator<<(std::ostream& out, const PostdecrementExpr& e);
	friend class TextDumper;	friend class ActivityGraphDumper;
};

#endif
