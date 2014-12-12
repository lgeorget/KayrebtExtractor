#ifndef PREINCREMENT_EXPR
#define PREINCRMEENT_EXPR

#include <string>
#include <gcc-plugin.h>
#include <tree.h>
#include "expression.h"

class PreincrementExpr : public Expression
{
	public:
		explicit PreincrementExpr(tree t);

	private:
		std::string variable;
};

#endif
