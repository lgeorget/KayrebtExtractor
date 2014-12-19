#ifndef CALL_EXPR_H
#define CALL_EXPR_H

#include <iostream>
#include <memory>
#include <string>
#include <list>
#include <gcc-plugin.h>
#include <tree.h>
#include "value.h"

class CallExpr : public Value
{
	public:
		explicit CallExpr(tree t);
		std::string print() const override; // Visitor design pattern

	private:
		long int _nbArgs;
		std::shared_ptr<Value> _name;
		std::list<std::shared_ptr<Value>> _args;
		std::string _built_str;
};

#endif
