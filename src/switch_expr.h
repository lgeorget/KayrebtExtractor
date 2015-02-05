#ifndef SWITCH_EXPR_H
#define SWITCH_EXPR_H

#include <iostream>
#include <memory>
#include <vector>
#include <gcc-plugin.h>
#include <gimple.h>
#include "expression.h"
#include "value.h"

class Dumper;

class SwitchExpr : public Expression
{
	public:
		explicit SwitchExpr(gimple t);
		void accept(Dumper& d) override;

	private:
		std::shared_ptr<Value> _var;
		std::vector<std::shared_ptr<Expression>> _labels;

	friend class TextDumper;
	friend class ActivityGraphDumper;
};

#endif
