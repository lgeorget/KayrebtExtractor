#include <iostream>
#include <memory>
#include <gcc-plugin.h>
#include <tree.h>
#include "expr_factory.h"
#include "expression.h"
#include "call_expr.h"
#include "decl_expr.h"
#include "expr_factory.h"
#include "expression.h"
#include "goto_expr.h"
#include "label_expr.h"
#include "modify_expr.h"
#include "preincrement_expr.h"
#include "return_expr.h"

const ExprFactory ExprFactory::INSTANCE;

std::unique_ptr<Expression> ExprFactory::build(tree t) const
{
	switch (TREE_CODE(t)) {
		case DECL_EXPR:
			return std::unique_ptr<Expression>(new DeclExpr(t));
		case CALL_EXPR:
			return std::unique_ptr<Expression>(new CallExpr(t));
		case GOTO_EXPR:
			return std::unique_ptr<Expression>(new GotoExpr(t));
		case LABEL_EXPR:
			return std::unique_ptr<Expression>(new LabelExpr(t));
		case MODIFY_EXPR:
			return std::unique_ptr<Expression>(new ModifyExpr(t));
		case PREINCREMENT_EXPR:
			return std::unique_ptr<Expression>(new PreincrementExpr(t));
		case RETURN_EXPR:
			return std::unique_ptr<Expression>(new ReturnExpr(t));
		case PREDECREMENT_EXPR:
		case POSTDECREMENT_EXPR:
		case POSTINCREMENT_EXPR:
		case LOOP_EXPR:
		case EXIT_EXPR:
		default:
			return std::unique_ptr<Expression>(new Expression(t));
	}
}


