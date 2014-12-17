#ifndef CASE_LABEL_EXPR_H
#define CASE_LABEL_EXPR_H

#include <iostream>
#include <memory>
#include <gcc-plugin.h>
#include <tree.h>
#include "expression.h"
#include "value.h"

class CaseLabelExpr : public Expression
{
	public:
		explicit CaseLabelExpr(tree t);
		virtual void accept(Dumper& d);

	private:
		std::shared_ptr<Value> _highValue;
		std::shared_ptr<Value> _lowValue;
		std::shared_ptr<Value> _label;

	friend class Dumper;
};

#endif

