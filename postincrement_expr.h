#ifndef POSTINCREMENT_EXPR_H
#define POSTINCREMENT_EXPR_H

#include <iostream>
#include <memory>
#include <string>
#include <gcc-plugin.h>
#include <tree.h>
#include "expression.h"

class Value;

class PostincrementExpr : public Expression
{
	public:
		explicit PostincrementExpr(tree t);
		virtual void accept(Dumper& d); // Visitor design pattern

	private:
		std::shared_ptr<Value> _variable;

	friend std::ostream& operator<<(std::ostream& out, const PostincrementExpr& e);
	friend class TextDumper;	friend class ActivityGraphDumper;
};

#endif
