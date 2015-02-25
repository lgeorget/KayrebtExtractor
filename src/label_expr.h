#ifndef LABEL_EXPR_H
#define LABEL_EXPR_H

#include <iostream>
#include <memory>
#include <gcc-plugin.h>
#include <gimple.h>
#include "expression.h"
#include "value.h"

class LabelExpr : public Expression
{
	public:
		explicit LabelExpr(gimple t);
		virtual void accept(Dumper& d); // Visitor design pattern

	private:
		std::shared_ptr<Value> _label;

	friend class ActivityGraphDumper;
};

#endif
