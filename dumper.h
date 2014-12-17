#ifndef DUMPER_H
#define DUMPER_H

#include <iostream>
#include <gcc-plugin.h>
#include <tree.h>
#include "boolean_expr.h"
#include "call_expr.h"
#include "cond_expr.h"
#include "compare_expr.h"
#include "decl_expr.h"
#include "expression.h"
#include "goto_expr.h"
#include "label_expr.h"
#include "modify_expr.h"
#include "preincrement_expr.h"
#include "return_expr.h"

class Dumper
{
	public:
		Dumper(std::ostream* const out = &std::cout, bool withHeader = true);
		void dumpBooleanExpr(BooleanExpr* const e);
		void dumpCallExpr(CallExpr* const e);
		void dumpCondExpr(CondExpr* const e);
		void dumpCompareExpr(CompareExpr* const e);
		void dumpDeclExpr(DeclExpr* const e);
		void dumpGotoExpr(GotoExpr* const e);
		void dumpLabelExpr(LabelExpr* const e);
		void dumpModifyExpr(ModifyExpr* const e);
		void dumpPreincrementExpr(PreincrementExpr* const e);
		void dumpReturnExpr(ReturnExpr* const e);
		void dumpExpression(Expression* const e);

	private:
		void header();
		std::ostream* const _out;
		bool _withHeader;
};


#endif
