#ifndef FUNCTION_BODY_H
#define FUNCTION_BODY_H

#include <iostream>
#include <vector>
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
		std::vector<std::pair<basic_block,std::vector<std::shared_ptr<Expression>>>> _bb;
		function* _fn;

	friend class ActivityGraphDumper;
};

#endif

