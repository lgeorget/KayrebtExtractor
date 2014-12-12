#ifndef DECL_EXPR_H
#define DECL_EXPR_H

#include <gcc-plugin.h>
#include <tree.h>
#include "expression.h"
#include "bad_tree_exception.h"

class DeclExpr : public Expression
{
	public:
		explicit DeclExpr(tree t);

	private:
		std::string _name;
};

#endif
