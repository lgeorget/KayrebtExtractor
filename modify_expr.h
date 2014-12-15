#ifndef MODIFY_EXPR_H
#define MODIFY_EXPR_H

#include <gcc-plugin.h>
#include <tree.h>
#include "expression.h"

class ModifyExpr : public Expression
{
	public:
		explicit ModifyExpr(tree t);
		virtual void accept(Dumper& d); // Visitor design pattern

	protected:
		const char* _whatToSet;
		const char* _newValue;

	friend std::ostream& operator<<(std::ostream& out, const ModifyExpr& e);
};

#endif
