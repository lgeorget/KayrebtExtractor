#ifndef FUNCTION_BODY_H
#define FUNCTION_BODY_H

#include <iostream>
#include <list>
#include <memory>
#include <gcc-plugin.h>
#include <tree.h>
#include <gimple.h>
#include <function.h>
#include "expression.h"

class Dumper;

class FunctionBody
{
	public:
		explicit FunctionBody(function* t);
		void accept(Dumper& d);

	private:
		std::list<std::shared_ptr<Expression>> _exprs;
		function* _fn;

	friend class TextDumper;
	friend class ActivityGraphDumper;
};

#endif

