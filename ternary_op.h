#ifndef TERNARY_OP_H
#define TERNARY_OP_H

#include <iostream>
#include <string>
#include <memory>
#include <gcc-plugin.h>
#include <tree.h>
#include "value.h"
#include "expression.h"

class TernaryOp : public Value
{
	public:
		explicit TernaryOp(tree t);
		std::string print() const override;

	private:
		std::shared_ptr<Expression> _cond;
		std::shared_ptr<Value> _yes;
		std::shared_ptr<Value> _no;
};

#endif
