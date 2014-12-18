#include <iostream>
#include <memory>
#include <gcc-plugin.h>
#include <tree.h>
#include "expr_factory.h"
#include "expression.h"
#include "arith_expr.h"
#include "bind_expr.h"
#include "call_expr.h"
#include "cond_expr.h"
#include "case_label_expr.h"
#include "decl_expr.h"
#include "expr_factory.h"
#include "expression.h"
#include "goto_expr.h"
#include "label_expr.h"
#include "modify_expr.h"
#include "preincrement_expr.h"
#include "return_expr.h"
#include "switch_expr.h"
#include "stmt_list.h"
#include "leaf.h"

ExprFactory ExprFactory::INSTANCE;

std::shared_ptr<Expression> ExprFactory::build(tree t)
{
	switch (TREE_CODE(t)) {
		case BIND_EXPR:
			return std::make_shared<BindExpr>(BindExpr(t));
		case DECL_EXPR:
		//	std::cerr << "...building Decl" << std::endl;
			return std::make_shared<DeclExpr>(DeclExpr(t));
		case CALL_EXPR:
		//	std::cerr << "...building Call" << std::endl;
			return std::make_shared<CallExpr>(CallExpr(t));
		case CASE_LABEL_EXPR:
			return std::make_shared<CaseLabelExpr>(CaseLabelExpr(t));
		case COND_EXPR:
		//	std::cerr << "...building Cond" << std::endl;
			return std::make_shared<CondExpr>(CondExpr(t));
		case GOTO_EXPR:
		//	std::cerr << "...building Goto" << std::endl;
			return std::make_shared<GotoExpr>(GotoExpr(t));
		case LABEL_EXPR:
		//	std::cerr << "...building Label" << std::endl;
			return std::make_shared<LabelExpr>(LabelExpr(t));
		case MODIFY_EXPR:
		//	std::cerr << "...building Modify" << std::endl;
			return std::make_shared<ModifyExpr>(ModifyExpr(t));

		// 'don't care'-expressions
		case CONVERT_EXPR:
		case NOP_EXPR:
			return build(TREE_OPERAND(t,0));

		// 'really don't care'-expressions
		case PREDICT_EXPR:
			return std::make_shared<Expression>(Expression(t));

		case 127: //PREINCREMENT_EXPR
			return std::make_shared<PreincrementExpr>(PreincrementExpr(t));
		case SWITCH_EXPR:
			return std::make_shared<SwitchExpr>(SwitchExpr(t));

		case STATEMENT_LIST:
			return std::make_shared<StmtList>(StmtList(t));

		case RETURN_EXPR:
		//	std::cerr << "...building Return" << std::endl;
			return std::make_shared<ReturnExpr>(ReturnExpr(t));

		case PREDECREMENT_EXPR:
		case POSTDECREMENT_EXPR:
		case POSTINCREMENT_EXPR:
		default:
		//	std::cerr << "...building Expr" << std::endl;
			return std::make_shared<Leaf>(Leaf(t));
	}
}


