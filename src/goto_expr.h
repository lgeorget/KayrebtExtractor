#ifndef GOTO_EXPR_H
#define GOTO_EXPR_H

#include <iostream>
#include <memory>
#include <gcc-plugin.h>
#include <gimple.h>
#include "expression.h"
#include "value.h"
#include "label.h"

class GotoExpr : public Expression
{
	public:
		explicit GotoExpr(gimple t);
		virtual void accept(Dumper& d); // Visitor design pattern

	private:
		// that probably supports computed gotos as well
		std::shared_ptr<Value> _label;

	friend class TextDumper;	friend class ActivityGraphDumper;
};

#endif
