#ifndef STRING_CST_H
#define STRING_CST_H

#include <iostream>
#include <string>
#include <gcc-plugin.h>
#include <tree.h>
#include "value.h"

class StringCst : public Value
{
	public:
		explicit StringCst(tree t);
		std::string print() const override;

	private:
		std::string _built_str;
};

#endif
