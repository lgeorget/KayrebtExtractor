#ifndef GOTO_EXPR_H
#define GOTO_EXPR_H

#include <iostream>
#include <memory>
#include <gcc-plugin.h>
#include <tree.h>
#include "expression.h"
#include "value.h"
#include "label.h"

class GotoExpr : public Expression
{
	public:
		explicit GotoExpr(tree t);
		virtual void accept(Dumper& d); // Visitor design pattern

	private:
		std::shared_ptr<Value> _label;

	friend std::ostream& operator<<(std::ostream& out, const GotoExpr& e);
	friend class TextDumper;	friend class ActivityGraphDumper;
};

#endif
