#include <cstdlib>
#include <iostream>
#include <stdexcept>
#include <string>
#include <memory>
#include <gcc-plugin.h>
#include "activity_graph_dumper.h"
#include "bind_expr.h"
#include "call_expr.h"
#include "case_label_expr.h"
#include "cond_expr.h"
#include "compound_expr.h"
#include "decl_expr.h"
#include "expression.h"
#include "goto_expr.h"
#include "label_expr.h"
#include "leaf.h"
#include "modify_expr.h"
#include "nop_expr.h"
#include "preincrement_expr.h"
#include "return_expr.h"
#include "stmt_list.h"
#include "switch_expr.h"
#include "dumper.h"
#include "node.h"
#include "activity_graph.h"

//ActivityGraphDumper::ActivityGraphDumper() : Dumper()
//{}

void ActivityGraphDumper::dumpExpression(Expression* const e)
{
}

void ActivityGraphDumper::dumpBindExpr(BindExpr* const e)
{
	e->_body->accept(*this);
	/*
	*_out << "*** start of inner scope ***" << std::endl;
// Vars are declared in body too
//	e->_vars->accept(*this);
	e->_body->accept(*this);
	*_out << "*** end of inner scope ***";
	*/
}

void ActivityGraphDumper::dumpCaseLabelExpr(CaseLabelExpr* const e)
{
	_g.addNode(std::make_shared<Node>(e->_label->print(), reinterpret_cast<uintptr_t>(e->_label.get())));
}

void ActivityGraphDumper::dumpCondExpr(CondExpr* const e)
{
	/*
	e->_cond->accept(*this);
	e->_then->accept(*this);
	if (e->_else) {
		*_out << "\n\telse ";
		e->_else->accept(*this);
	}
	*/
}

void ActivityGraphDumper::dumpCompoundExpr(CompoundExpr* const e)
{
	/*
	e->_first->accept(*this);
	e->_second->accept(*this);
	*/
}

void ActivityGraphDumper::dumpDeclExpr(DeclExpr* const e)
{
}

void ActivityGraphDumper::dumpGotoExpr(GotoExpr* const e)
{
}

void ActivityGraphDumper::dumpLabelExpr(LabelExpr* const e)
{
}

void ActivityGraphDumper::dumpLeaf(Leaf* const e)
{
}

void ActivityGraphDumper::dumpModifyExpr(ModifyExpr* const e)
{
}

void ActivityGraphDumper::dumpNopExpr(NopExpr* const e)
{
}

void ActivityGraphDumper::dumpPreincrementExpr(PreincrementExpr* const e)
{
}

void ActivityGraphDumper::dumpReturnExpr(ReturnExpr* const e)
{
	/*
	if (e->_value) {
		*_out << " : ";
		e->_value->accept(*this);
	}
	*/
}

void ActivityGraphDumper::dumpStmtList(StmtList* const e)
{
	/*
	for (auto expr : e->_exprs) {
		expr->accept(*this);
		*_out << std::endl;
	}
	*/
}

void ActivityGraphDumper::dumpSwitchExpr(SwitchExpr* const e)
{
	/*
	e->_cond->accept(*this);
	e->_body->accept(*this);
	*_out << "*** end of switch ***";
	*/
}

void ActivityGraphDumper::updateCurrent()
{
}

