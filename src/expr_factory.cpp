#include <iostream>
#include <memory>
#include <gcc-plugin.h>
#include <gimple.h>
#include <tree.h>
#include <function.h>
#include "expr_factory.h"
#include "expression.h"
#include "asm_expr.h"
#include "assign_expr.h"
#include "call_expr.h"
#include "cond_expr.h"
#include "expr_factory.h"
#include "expression.h"
#include "goto_expr.h"
#include "label_expr.h"
#include "return_expr.h"
#include "switch_expr.h"
#include "bb_list.h"

ExprFactory ExprFactory::INSTANCE;

std::shared_ptr<Expression> ExprFactory::build(gimple t)
{
	switch (gimple_code(t)) {
		case GIMPLE_ASM:
			std::cerr << "...building Asm" << std::endl;
			return std::make_shared<AsmExpr>(AsmExpr(t));

		case GIMPLE_ASSIGN:
			std::cerr << "...building Assign" << std::endl;
			return std::make_shared<AssignExpr>(AssignExpr(t));

		case GIMPLE_CALL:
			std::cerr << "...building Call" << std::endl;
			return std::make_shared<CallExpr>(CallExpr(t));

		case GIMPLE_COND:
			std::cerr << "...building Cond" << std::endl;
			return std::make_shared<CondExpr>(CondExpr(t));

		case GIMPLE_LABEL:
			std::cerr << "...building Label" << std::endl;
			return std::make_shared<LabelExpr>(LabelExpr(t));

		case GIMPLE_GOTO:
			std::cerr << "...building Goto" << std::endl;
			return std::make_shared<GotoExpr>(GotoExpr(t));

		case GIMPLE_SWITCH:
			std::cerr << "...building Switch" << std::endl;
			return std::make_shared<SwitchExpr>(SwitchExpr(t));

		case GIMPLE_RETURN:
			std::cerr << "...building Return" << std::endl;
			return std::make_shared<ReturnExpr>(ReturnExpr(t));

		// 'don't care'-expressions
		case GIMPLE_PREDICT:
		case GIMPLE_NOP:
		default:
			return std::make_shared<Expression>(Expression(t));
	}
}

std::shared_ptr<BbList> ExprFactory::build(function* fn)
{
	return std::make_shared<BbList>(BbList(fn));
}



