#ifndef NEGATE_OP_H
#define NEGATE_OP_H

#include <iostream>
#include <string>
#include <gcc-plugin.h>
#include <tree.h>
#include "value.h"

class NegateOp : public Value
{
	public:
		explicit NegateOp(tree t, std::string op);
		virtual std::string print() const;

	private:
		std::shared_ptr<Value> _val;
		std::string _op;
};

#endif
