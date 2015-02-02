#ifndef ARITH_EXPR_H
#define ARITH_EXPR_H

#include <iostream>
#include <string>
#include <memory>
#include <gcc-plugin.h>
#include <tree.h>
#include "value.h"

class Dumper;

class ArithExpr : public Value
{
	public:
		explicit ArithExpr(tree t, std::string op);
		std::string print() const override;

	private:
		const std::string _op;
		std::shared_ptr<Value> _opl;
		std::shared_ptr<Value> _opr;
};

#endif
