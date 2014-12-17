#include <iostream>
#include <memory>
#include <gcc-plugin.h>
#include <tree.h>
#include "expr_factory.h"
#include "expression.h"
#include "boolean_expr.h"
#include "call_expr.h"
#include "cond_expr.h"
#include "compare_expr.h"
#include "decl_expr.h"
#include "expr_factory.h"
#include "expression.h"
#include "goto_expr.h"
#include "label_expr.h"
#include "modify_expr.h"
#include "preincrement_expr.h"
#include "return_expr.h"

const ExprFactory ExprFactory::INSTANCE;

std::shared_ptr<Expression> ExprFactory::build(tree t) const
{
	switch (TREE_CODE(t)) {
		case DECL_EXPR:
		//	std::cerr << "...building Decl" << std::endl;
			return std::shared_ptr<Expression>(new DeclExpr(t));
		case CALL_EXPR:
		//	std::cerr << "...building Call" << std::endl;
			return std::shared_ptr<Expression>(new CallExpr(t));
		case COND_EXPR:
		//	std::cerr << "...building Cond" << std::endl;
			return std::shared_ptr<Expression>(new CondExpr(t));
		case GOTO_EXPR:
		//	std::cerr << "...building Goto" << std::endl;
			return std::shared_ptr<Expression>(new GotoExpr(t));
		case LABEL_EXPR:
		//	std::cerr << "...building Label" << std::endl;
			return std::shared_ptr<Expression>(new LabelExpr(t));
		case MODIFY_EXPR:
		//	std::cerr << "...building Modify" << std::endl;
			return std::shared_ptr<Expression>(new ModifyExpr(t));
		case 127: //PREINCREMENT_EXPR
			return std::shared_ptr<Expression>(new PreincrementExpr(t));
		case RETURN_EXPR:
		//	std::cerr << "...building Return" << std::endl;
			return std::shared_ptr<Expression>(new ReturnExpr(t));
		case TRUTH_ANDIF_EXPR:
		case TRUTH_AND_EXPR:
			return std::shared_ptr<Expression>(new BooleanExpr(t,"&&"));
		case TRUTH_ORIF_EXPR:
		case TRUTH_OR_EXPR:
			return std::shared_ptr<Expression>(new BooleanExpr(t,"||"));
		case TRUTH_XOR_EXPR: //Doesn't exist in C, AFAIR...
			return std::shared_ptr<Expression>(new BooleanExpr(t,"^"));
		case LT_EXPR:
			return std::shared_ptr<Expression>(new CompareExpr(t,"<"));
		case LE_EXPR:
			return std::shared_ptr<Expression>(new CompareExpr(t,"<="));
		case GT_EXPR:
			return std::shared_ptr<Expression>(new CompareExpr(t,">"));
		case GE_EXPR:
			return std::shared_ptr<Expression>(new CompareExpr(t,">="));
		case EQ_EXPR:
			return std::shared_ptr<Expression>(new CompareExpr(t,"=="));
		case NE_EXPR:
			return std::shared_ptr<Expression>(new CompareExpr(t,"!="));


		case PREDECREMENT_EXPR:
		case POSTDECREMENT_EXPR:
		case POSTINCREMENT_EXPR:
		case LOOP_EXPR:
		case EXIT_EXPR:
		default:
		//	std::cerr << "...building Expr" << std::endl;
			return std::shared_ptr<Expression>(new Expression(t));
	}
}


