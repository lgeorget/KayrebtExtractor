#ifndef CALL_EXPR_H
#define CALL_EXPR_H

#include <list>
#include <gcc-plugin.h>
#include <tree.h>
#include "expression.h"

class CallExpr : public Expression
{
	public:
		explicit CallExpr(tree t);

	private:
		int _nbArgs;
		const char* _name;
//		std::list<Value> _args;

	friend std::ostream& operator<<(std::ostream& out, const CallExpr& e);
};

#endif
