/**
 * \file expr_factory.cpp
 * \author Laurent Georget
 * \date 2015-03-03
 * \brief Implementation of the ExprFactory
 */
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
#include "function_body.h"

ExprFactory ExprFactory::INSTANCE;

std::shared_ptr<Expression> ExprFactory::build(gimple t)
{
	switch (gimple_code(t)) {
		case GIMPLE_ASM:
			return std::make_shared<AsmExpr>(AsmExpr(t));

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

		case GIMPLE_ASSIGN:
			if (!gimple_clobber_p(t))
				return std::make_shared<AssignExpr>(AssignExpr(t));
			// else falltrough to the don't-care case

		// 'don't care'-expressions
		case GIMPLE_PREDICT:
		case GIMPLE_NOP:
		case GIMPLE_DEBUG:
			return std::make_shared<Expression>(Expression(t));

		default:
			throw std::runtime_error(gimple_code_name[gimple_code(t)]);
	}
}

std::shared_ptr<FunctionBody> ExprFactory::build(function* fn)
{
	return std::make_shared<FunctionBody>(FunctionBody(fn));
}



