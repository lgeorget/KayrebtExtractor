#ifndef INDIRECTION_H
#define INDIRECTION_H

#include <iostream>
#include <gcc-plugin.h>
#include <tree.h>
#include "value.h"

class Indirection : public Value
{
	public:
		explicit Indirection(tree t, std::string&& op);
		std::string print() const override;

	private:
		std::shared_ptr<Value> _val;
		std::string _op;
};

#endif
