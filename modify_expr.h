#ifndef MODIFY_EXPR_H
#define MODIFY_EXPR_H

#include <gcc-plugin.h>
#include <tree.h>
#include "expression.h"

class ModifyExpr : public Expression
{
	public:
		explicit ModifyExpr(tree t);

	protected:
		const char* _whatToSet;
		const char* _newValue;
};

#endif
