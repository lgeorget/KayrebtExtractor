#include <iostream>
#include <memory>
#include <gcc-plugin.h>
#include <tree.h>
#include "expr_factory.h"
#include "expression.h"
#include "cond_expr.h"
#include "case_label_expr.h"
#include "decl_expr.h"
#include "expr_factory.h"
#include "expression.h"
#include "goto_expr.h"
#include "label_expr.h"
#include "modify_expr.h"
#include "return_expr.h"
#include "switch_expr.h"
#include "bb_list.h"
#include "leaf.h"

ExprFactory ExprFactory::INSTANCE;

std::shared_ptr<Expression> ExprFactory::build(gimple t)
{
	switch (gimple_code(t)) {
		case DECL_EXPR:
		//	std::cerr << "...building Decl" << std::endl;
			return std::make_shared<DeclExpr>(DeclExpr(t));
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
		case NOP_EXPR:
			return build(TREE_OPERAND(t,0));

		// 'really don't care'-expressions
		case PREDICT_EXPR:
			return std::make_shared<Expression>(Expression(t));

		case SWITCH_EXPR:
			return std::make_shared<SwitchExpr>(SwitchExpr(t));

		case RETURN_EXPR:
		//	std::cerr << "...building Return" << std::endl;
			return std::make_shared<ReturnExpr>(ReturnExpr(t));

		default:
		//	std::cerr << "...building Expr" << std::endl;
			return std::make_shared<Leaf>(Leaf(t));
	}
}

std::shared_ptr<Expression> ExprFactory::build(basic_block bb)
{
	return std::make_shared<BbList>(BbList bb));
}



