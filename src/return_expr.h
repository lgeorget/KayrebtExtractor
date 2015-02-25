#ifndef RETURN_EXPR_H
#define RETURN_EXPR_H

#include <iostream>
#include <memory>
#include <gcc-plugin.h>
#include <gimple.h>
#include "expression.h"
#include "value.h"

class ReturnExpr : public Expression
{
	public:
		explicit ReturnExpr(gimple t);
		virtual void accept(Dumper& d); // Visitor design pattern

	private:
		std::shared_ptr<Value> _value;

	friend class ActivityGraphDumper;
};

#endif
