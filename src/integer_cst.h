#ifndef INTEGER_CST_H
#define INTEGER_CST_H

#include <iostream>
#include <string>
#include <gcc-plugin.h>
#include <tree.h>
#include "value.h"

class IntegerCst : public Value
{
	public:
		explicit IntegerCst(tree t);
		std::string print() const override;

	private:
		int _integ;
};

#endif
