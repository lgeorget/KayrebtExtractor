#ifndef STMT_LIST_H
#define STMT_LIST_H

#include <iostream>
#include <list>
#include <memory>
#include <gcc-plugin.h>
#include <tree.h>
#include "expression.h"

class Dumper;

class StmtList : public Expression
{
	public:
		explicit StmtList(tree t);
		void accept(Dumper& d);

	private:
		std::list<std::shared_ptr<Expression>> _exprs;

	friend class TextDumper;	friend class ActivityGraphDumper;
};

#endif

