#ifndef CALL_EXPR_H
#define CALL_EXPR_H

#include <iostream>
#include <memory>
#include <list>
#include <gcc-plugin.h>
#include <tree.h>
#include "expression.h"
#include "value.h"

class CallExpr : public Expression
{
	public:
		explicit CallExpr(tree t);
		virtual void accept(Dumper& d); // Visitor design pattern

	private:
		long int _nbArgs;
		const char* _name;
		std::list<std::shared_ptr<Value>> _args;

	friend std::ostream& operator<<(std::ostream& out, const CallExpr& e);
};

#endif
