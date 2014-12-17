#ifndef SWITCH_EXPR_H
#define SWITCH_EXPR_H

#include <iostream>
#include <memory>
#include <gcc-plugin.h>
#include <tree.h>
#include "expression.h"

class Dumper;

class SwitchExpr : public Expression
{
	public:
		explicit SwitchExpr(tree t);
		void accept(Dumper& d) override;

	private:
		std::shared_ptr<Expression> _cond;
		std::shared_ptr<Expression> _body;

	friend class Dumper;
};

#endif
