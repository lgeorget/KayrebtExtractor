#ifndef LABEL_EXPR_H
#define LABEL_EXPR_H

#include <iostream>
#include <memory>
#include <gcc-plugin.h>
#include <tree.h>
#include "expression.h"
#include "value.h"

class LabelExpr : public Expression
{
	public:
		explicit LabelExpr(tree t);
		virtual void accept(Dumper& d); // Visitor design pattern

	private:
		std::shared_ptr<Value> _label;

	friend std::ostream& operator<<(std::ostream& out, const LabelExpr& e);
	friend class TextDumper;	friend class ActivityGraphDumper;
};

#endif
