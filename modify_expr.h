#ifndef MODIFY_EXPR_H
#define MODIFY_EXPR_H

#include <iostream>
#include <memory>
#include <gcc-plugin.h>
#include <tree.h>
#include "expression.h"
#include "value.h"

class ModifyExpr : public Expression
{
	public:
		explicit ModifyExpr(tree t);
		virtual void accept(Dumper& d); // Visitor design pattern

	protected:
		std::shared_ptr<Value> _whatToSet;
		std::shared_ptr<Value> _newValue;

	friend std::ostream& operator<<(std::ostream& out, const ModifyExpr& e);
};

#endif
