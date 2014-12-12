#ifndef DUMPER_H
#define DUMPER_H

#include <iostream>
#include <memory>
#include <gcc-plugin.h>
#include <tree.h>
#include "call_expr.h"
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
		Dumper() = default;
		void dumpCallExpr(std::shared_ptr<CallExpr> e);
		void dumpDeclExpr(std::shared_ptr<DeclExpr> e);
		void dumpGotoExpr(std::shared_ptr<GotoExpr> e);
		void dumpLabelExpr(std::shared_ptr<LabelExpr> e);
		void dumpModifyExpr(std::shared_ptr<ModifyExpr> e);
		void dumpPreincrementExpr(std::shared_ptr<PreincrementExpr> e);
		void dumpReturnExpr(std::shared_ptr<ReturnExpr> e);
		void dumpExpression(std::shared_ptr<Expression> e);

	private:
		std::ostream& header();
		std::ostream dumpChannel;
};


#endif
