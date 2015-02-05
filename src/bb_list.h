#ifndef BB_LIST_H
#define BB_LIST_H

#include <iostream>
#include <list>
#include <memory>
#include <gcc-plugin.h>
#include <tree.h>
#include <gimple.h>
#include "expression.h"

class Dumper;

class BbList : public Expression
{
	public:
		explicit BbList(basic_block t);
		void accept(Dumper& d);

	private:
		std::list<std::shared_ptr<Expression>> _exprs;

	friend class TextDumper;	friend class ActivityGraphDumper;
};

#endif

