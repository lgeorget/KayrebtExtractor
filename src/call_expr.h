#ifndef CALL_EXPR_H
#define CALL_EXPR_H

#include <iostream>
#include <memory>
#include <string>
#include <list>
#include <gcc-plugin.h>
#include <gimple.h>
#include "expression.h"
#include "value.h"

class CallExpr : public Expression
{
	public:
		explicit CallExpr(gimple t);
		std::string print() const override; // Visitor design pattern

	private:
		unsigned int _nbArgs;
		std::shared_ptr<Value> _var;
		std::shared_ptr<Value> _name;
		std::list<std::shared_ptr<Value>> _args;
		std::string _built_str;
};

#endif
