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
			return std::make_shared<AsmExpr>(AsmExpr(t));

		case GIMPLE_ASSIGN:
			return std::make_shared<AssignExpr>(AssignExpr(t));

		case GIMPLE_CALL:
			return std::make_shared<CallExpr>(CallExpr(t));

		case GIMPLE_COND:
			return std::make_shared<CondExpr>(CondExpr(t));

		case GIMPLE_LABEL:
			return std::make_shared<LabelExpr>(LabelExpr(t));

		case GIMPLE_GOTO:
			return std::make_shared<GotoExpr>(GotoExpr(t));

		case GIMPLE_SWITCH:
			return std::make_shared<SwitchExpr>(SwitchExpr(t));

		case GIMPLE_RETURN:
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



