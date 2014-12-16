#ifndef RVALUE_H
#define RVALUE_H

#include <iostream>
#include <sstream>
#include <type_traits>
#include <gcc-plugin.h>
#include <tree.h>
#include "value.h"
#include "expression.h"

template <typename E>
class RValue : public Value, protected E
{
	static_assert(std::is_base_of<Expression, E>::value, "RValue must inherits from Expression");

	public:
		explicit RValue(tree t) : Value(t), E(t) 
		{
			std::ostringstream out;
			out << *this; 
			_content = out.str();
		}
		std::string print() const override
		{
			return _content;
		}

	private:
		std::string _content;
};

#endif
