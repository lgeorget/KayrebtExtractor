#ifndef NOP_EXPR_H
#define NOP_EXPR_H

#include <iostream>
#include <memory>
#include <list>
#include <gcc-plugin.h>
#include <tree.h>
#include "expression.h"

class NopExpr : public Expression
{
	public:
		explicit NopExpr(tree t);
		void accept(Dumper& d) override;

	friend class TextDumper;	friend class ActivityGraphDumper;
};

#endif
