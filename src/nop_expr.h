#ifndef NOP_EXPR_H
#define NOP_EXPR_H

#include <iostream>
#include <memory>
#include <list>
#include <gcc-plugin.h>
#include <gimple.h>
#include "expression.h"

class NopExpr : public Expression
{
	public:
		explicit NopExpr(gimple t);
		void accept(Dumper& d) override;

	friend class ActivityGraphDumper;
};

#endif
