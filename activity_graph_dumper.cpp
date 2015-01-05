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
#include "label.h"

//ActivityGraphDumper::ActivityGraphDumper() : Dumper()
//{}

void ActivityGraphDumper::dumpExpression(Expression* const e)
{
}

void ActivityGraphDumper::dumpBindExpr(BindExpr* const e)
{
	e->_body->accept(*this);
}

void ActivityGraphDumper::dumpCaseLabelExpr(CaseLabelExpr* const e)
{
	_g.addNode(std::make_shared<Node>(e->_label->print(), reinterpret_cast<uintptr_t>(e)));
}

void ActivityGraphDumper::dumpCondExpr(CondExpr* const e)
{
	e->_cond->accept(*this);
	std::shared_ptr<Node> curr = _g.getCurrent();
	e->_then->accept(*this);
	if (e->_else) {
		_g.setCurrent(curr);
		e->_else->accept(*this);
	}
}

void ActivityGraphDumper::dumpCompoundExpr(CompoundExpr* const e)
{
	e->_first->accept(*this);
	e->_second->accept(*this);
}

void ActivityGraphDumper::dumpDeclExpr(DeclExpr* const e)
{
	_g.addNode(std::make_shared<Node>(e->_name->print(), reinterpret_cast<uintptr_t>(e)));
}

void ActivityGraphDumper::dumpGotoExpr(GotoExpr* const e)
{
	_g.fork(_g.getCurrent(), std::stoull(e->_label->print()));
}

void ActivityGraphDumper::dumpLabelExpr(LabelExpr* const e)
{
	auto node =  _g.getLabel(std::stoull(e->_label->print()));
	_g.fork(_g.getCurrent(), node->getNid());
	_g.setCurrent(node);
}

void ActivityGraphDumper::dumpLeaf(Leaf* const e)
{
	_g.addNode(std::make_shared<Node>(e->_val->print(), reinterpret_cast<uintptr_t>(e)));
}

void ActivityGraphDumper::dumpModifyExpr(ModifyExpr* const e)
{
	_g.addNode(std::make_shared<Node>(e->_whatToSet->print() + " = " + e->_newValue->print(),
				reinterpret_cast<uintptr_t>(e)));
}

void ActivityGraphDumper::dumpNopExpr(NopExpr* const e)
{
}

void ActivityGraphDumper::dumpPreincrementExpr(PreincrementExpr* const e)
{
	_g.addNode(std::make_shared<Node>(e->_variable->print() + "++",
				reinterpret_cast<uintptr_t>(e)));
}

void ActivityGraphDumper::dumpReturnExpr(ReturnExpr* const e)
{
	if (e->_value)
		e->_value->accept(*this);
}

void ActivityGraphDumper::dumpStmtList(StmtList* const e)
{
	for (auto expr : e->_exprs) {
		expr->accept(*this);
	}
}

void ActivityGraphDumper::dumpSwitchExpr(SwitchExpr* const e)
{
	e->_cond->accept(*this);
	e->_body->accept(*this);
}
