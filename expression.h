#ifndef EXPRESSION_H
#define EXPRESSION_H

#include <iostream>
#include <gcc-plugin.h>
#include <tree.h>

class Dumper;

class Expression
{
	public:
		explicit Expression(tree t);
		virtual ~Expression() = default;
		virtual void accept(Dumper& d); // Visitor design pattern

	private:
		tree _expr;
};

#endif
