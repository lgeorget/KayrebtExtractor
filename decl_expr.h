#ifndef DECL_EXPR_H
#define DECL_EXPR_H

#include <iostream>
#include <memory>
#include <gcc-plugin.h>
#include <tree.h>
#include "expression.h"
#include "value.h"

class DeclExpr : public Expression
{
	public:
		explicit DeclExpr(tree t);
		virtual void accept(Dumper& d); // Visitor design pattern

	private:
		std::shared_ptr<Value> _name;
		std::shared_ptr<Value> _init;
		
	friend class TextDumper;
};

#endif
