#ifndef EXPRESSION_H
#define EXPRESSION_H

#include <iostream>
#include <gcc-plugin.h>
#include <gimple.h>

class Dumper;

class Expression
{
	public:
		explicit Expression(gimple t);
		virtual ~Expression() = default;
		virtual void accept(Dumper& d); // Visitor design pattern

	private:
		gimple _expr;

	friend std::ostream& operator<<(std::ostream& out, const Expression& e);
};

#endif
